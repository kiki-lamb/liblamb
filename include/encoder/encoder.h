#ifndef LAMBOS_ENCODER_H
#define LAMBOS_ENCODER_H

#if ! defined(__AVR_ATtiny85__)
#include <Adafruit_MCP23017.h>
#include <util/atomic.h>
#endif

#include <stdlib.h>

#define KL_ENCODER_DEBUG

namespace lamb {
  namespace encoders {
    namespace states {

      //////////////////////////////////////////////////////////////////////////

      class i_state {
      public:
#if __cplusplus >= 201402L
        void operator delete(void * ptr) { free(ptr); }
#endif

        virtual ~i_state() {};
        inline void update(char bitpair);

      private:
        virtual void do_up() = 0;
        virtual void do_down() = 0;
        volatile uint16_t last_stages_ix = 0;
      };

      //////////////////////////////////////////////////////////////////////////

      template <char bits, bool invert = false>
      class uint : public i_state {
      public:
        typedef uint16_t value_type;

        volatile bool flagged = false;

        uint() {}
        virtual ~uint() {}
        inline void set_value(uint16_t v, bool raw = false);
        inline uint16_t value(bool raw = false) const;

      private:
        volatile uint16_t _value = 0;

        virtual void do_up() override;
        virtual void do_down() override;
        void adjust_value(int16_t delta);
      };

      //////////////////////////////////////////////////////////////////////////

      class uint_var : public i_state {
      public:
        typedef uint16_t value_type;

        volatile bool flagged = false;

        inline uint_var(char bits_ = 8);
        inline virtual ~uint_var() {};
        inline void set_value(uint16_t v);
        inline uint16_t value() const;

      private:
        char bits = 0;
        volatile uint16_t _value = 0;

        inline virtual void do_up() override;
        inline virtual void do_down() override;
        inline void adjust_value(int16_t delta);
      };

      //////////////////////////////////////////////////////////////////////////

      class directional : public i_state {
      public:
        enum direction_type {
          DIRECTION_DOWN = -1,
          DIRECTION_NONE = 0,
          DIRECTION_UP = 1
        };

      private:
        volatile direction_type direction_;

        inline virtual void do_up() override {
          direction_ = DIRECTION_UP;
        }

        inline virtual void do_down() override {
          direction_ = DIRECTION_DOWN;
        }

      public:
        volatile bool flagged = false;
        
        inline directional() : direction_(DIRECTION_NONE) {}

        inline virtual ~directional() {};
        
        inline direction_type direction() const {
          return direction_;
        }

      };

      //////////////////////////////////////////////////////////////////////////

      class func_ptr : public i_state {
      public:
        typedef void value_type;

        void(*up_func)() = 0;
        void(*down_func)() = 0;

        inline func_ptr() {}
        inline virtual ~func_ptr() {}
      private:
        volatile char value = 0;

        inline virtual void do_up() override;
        inline virtual void do_down() override;
      };
    }

    ////////////////////////////////////////////////////////////////////////////

    namespace interfaces {
      class i_interface {
      public:
#if __cplusplus >= 201402L
        void operator delete(void * ptr) { free(ptr); }
#endif

        virtual ~i_interface() {}
        virtual void setup(lamb::encoders::states::i_state * state) = 0;
        virtual void poll() = 0;
        virtual bool poll_required() = 0;
      };

      //////////////////////////////////////////////////////////////////////////

      template< char pin0, char pin1>
      class native_pins : public i_interface {
      public:
        virtual ~native_pins() {}
        native_pins() {}
        virtual void setup(lamb::encoders::states::i_state * state);
        virtual void poll();
        virtual bool poll_required();
        //			private:
        static lamb::encoders::states::i_state * state;
        static void update();
        static char             pin0_mask;
        static char             pin1_mask;
#ifdef __AVR__
        static volatile uint8_t* pin0_port;
        static volatile uint8_t* pin1_port;
#else
        static volatile uint32_t* pin0_port;
        static volatile uint32_t* pin1_port;
#endif
      };
    }

    ////////////////////////////////////////////////////////////////////////////

    class basic {
    public:
      lamb::encoders::states::i_state * state;
      lamb::encoders::interfaces::i_interface * interface;

      basic(lamb::encoders::states::i_state * state_ = 0, lamb::encoders::interfaces::i_interface * interface_ = 0) : state(state_), interface(interface_) {}

      inline void setup() {
        interface->setup(state);
      }
    };

    ////////////////////////////////////////////////////////////////////////////

    template <typename STATE_T, typename INTERFACE_T>
    class custom{
      /* static_assert(std::is_base_of<lamb::encoders::states::i_state, STATE_T>::value, "STATE_T must derive from Base"); */
      /* static_assert(std::is_base_of<lamb::encoders::interfaces::i_interface, INTERFACE_T>::value, "INTERFACE_T must derive from Base"); */
    public:
      typedef STATE_T state_type;
      typedef INTERFACE_T interface_type;

    private:
      state_type * _state;
      interface_type * _interface;

    public:
      inline state_type & state() {
        return *_state;
      }

      inline interface_type & interface() {
        return *_interface;
      }

      inline void setup() {
        //Serial.println("Setup encoder... ");
        _interface->setup(_state);
        //Serial.println("Done setup encoder. ");
      }

      custom(state_type * state_ = 0, interface_type * interface_ = 0) :
        _state(state_), _interface(interface_) {
        if (!_state) _state = new STATE_T();
        if (!_interface) _interface = new INTERFACE_T();
      }
    };

    ////////////////////////////////////////////////////////////////////////////

    template <char pin0, char pin1, char bits>
    class uint {
    public:
      inline static void     setup();
      inline static uint16_t value();
      inline static void     set_value(uint16_t v);
      inline static bool     flag();
      inline static void     set_flag(bool f);

    private:
      static states::uint<bits> state;
      uint();
    };

    ////////////////////////////////////////////////////////////////////////////

#if ! defined(__AVR_ATtiny85__)
    template <uint8_t irq_pin, uint8_t i2c_addr, typename state_t>
    class whole_mcp {
    public:
      typedef state_t state_type;
      inline static void     setup(
        Adafruit_MCP23017 * mcp_,
        bool attach = true
      );
      inline static state_type & state(uint8_t ix);
      inline static bool     poll(bool force = false);
      static volatile bool pending;
      static void mcp_irq();

    private:
      static Adafruit_MCP23017 * mcp;
      static state_type states[8];
      whole_mcp();
    };
#endif

    ////////////////////////////////////////////////////////////////////////////

    template <char pin0, char pin1>
    class func_ptr {
    public:
      inline static void setup(void(*up)() = 0, void(*down)() = 0);

    private:
      static states::func_ptr state;
      func_ptr();
    };
  }
};

////////////////////////////////////////////////////////////////////////////////
// lamb::encoders::states::i_state definitions
////////////////////////////////////////////////////////////////////////////////

void lamb::encoders::states::i_state::update(char bitpair) {
  static const unsigned char stages[] = { 0b11, 0b10, 0b00, 0b01 };

  if (stages[(last_stages_ix + 1) & 0b11] == bitpair) {
    //#ifdef KL_ENCODER_DEBUG
    ////Serial.print("update ^ ");
    ////Serial.print(last_stage, DEC);
    ////Serial.print(" -> ");
    ////Serial.print(bitpair, DEC);
    ////Serial.println();
    //#endif

    do_up();

    last_stages_ix = (last_stages_ix + 1) & 0b11;
  }
  else if (stages[((last_stages_ix - 1) &0b11)] == bitpair) {
    //#ifdef KL_ENCODER_DEBUG
    ////Serial.print("update v ");
    ////Serial.print(last_stage, DEC);
    ////Serial.print(" -> ");
    ////Serial.print(bitpair, DEC);
    ////Serial.println();
    //#endif

    do_down();

    last_stages_ix = (last_stages_ix - 1) & 0b11;
  }
  /* else { */
  /* 	//Serial.print("FUCK "); */
  /* 	//Serial.print(last_stage, DEC); */
  /* 	//Serial.print(" -> "); */
  /* 	//Serial.print(bitpair, DEC); */
  /* 	//Serial.println(); */
  /* } */
}

////////////////////////////////////////////////////////////////////////////////
// lamb::encoders::states::uint<> definitions
////////////////////////////////////////////////////////////////////////////////

template <char bits, bool invert>
uint16_t lamb::encoders::states::uint<bits,invert>::value(bool raw) const {
  return raw ? _value : (_value >> 2);
}

template <char bits, bool invert>
void lamb::encoders::states::uint<bits,invert>::set_value(uint16_t v, bool raw) {

  //Serial.print("Set encoder to ");
  //Serial.println(v);

  _value = raw ? v : (v << 2);
}

template <char bits, bool invert>
void lamb::encoders::states::uint<bits, invert>::adjust_value(int16_t delta) {
  uint16_t old_rough = value();
  int16_t new_value = invert ? _value - delta : _value + delta;
  _value = constrain(new_value, 0, (1 << (bits + 2)) - 1);
  flagged = value() != old_rough;
}

template <char bits, bool invert>
void lamb::encoders::states::uint<bits, invert>::do_up() {
  adjust_value(1);
}

template <char bits, bool invert>
void lamb::encoders::states::uint<bits, invert>::do_down() {
  adjust_value(-1);
}

////////////////////////////////////////////////////////////////////////////////
// lamb::encoders::states::uint_var definitions
////////////////////////////////////////////////////////////////////////////////

lamb::encoders::states::uint_var::uint_var(char bits_) : bits(bits_) {}

uint16_t lamb::encoders::states::uint_var::value() const {
  return _value >> 2;
}

void lamb::encoders::states::uint_var::set_value(uint16_t v) {
  _value = v << 2;
}

void lamb::encoders::states::uint_var::adjust_value(int16_t delta) {
  static uint16_t old_rough;
  old_rough = value();

  static int16_t new_value;
  new_value = _value + delta;

  _value = constrain(new_value, 0, (1 << (bits + 2)) - 1);

  flagged = _value != old_rough;
}


void lamb::encoders::states::uint_var::do_up() {
  adjust_value(1);
}

void lamb::encoders::states::uint_var::do_down() {
  adjust_value(-1);
}

////////////////////////////////////////////////////////////////////////////////
// lamb::encoders::states::func_ptr<> definitions
////////////////////////////////////////////////////////////////////////////////

void lamb::encoders::states::func_ptr::do_up() {
  up_func();
}

void lamb::encoders::states::func_ptr::do_down() {
  down_func();
}

////////////////////////////////////////////////////////////////////////////////
// lamb::encoders::interfaces::native_pins<> definitions
////////////////////////////////////////////////////////////////////////////////

template<char pin0, char pin1> lamb::encoders::states::i_state *  lamb::encoders::interfaces::native_pins<pin0, pin1>::state = 0;
template<char pin0, char pin1> char lamb::encoders::interfaces::native_pins<pin0, pin1>::pin0_mask = 0;
template<char pin0, char pin1> char lamb::encoders::interfaces::native_pins<pin0, pin1>::pin1_mask = 0;

#ifdef __AVR__
template<char pin0, char pin1> volatile uint8_t *  lamb::encoders::interfaces::native_pins<pin0, pin1>::pin0_port = 0;
template<char pin0, char pin1> volatile uint8_t *  lamb::encoders::interfaces::native_pins<pin0, pin1>::pin1_port = 0;
#else
template<char pin0, char pin1> volatile uint32_t *  lamb::encoders::interfaces::native_pins<pin0, pin1>::pin0_port = 0;
template<char pin0, char pin1> volatile uint32_t *  lamb::encoders::interfaces::native_pins<pin0, pin1>::pin1_port = 0;
#endif

template< char pin0, char pin1> void lamb::encoders::interfaces::native_pins<pin0, pin1>::poll() {}
template< char pin0, char pin1> bool lamb::encoders::interfaces::native_pins<pin0, pin1>::poll_required() { return false; }

template< char pin0, char pin1> void lamb::encoders::interfaces::native_pins<pin0, pin1>::setup(
  lamb::encoders::states::i_state * state_
) {
  //Serial.println("Setup interface (native_pins)... ");
  state = state_;
  pinMode(pin0, INPUT_PULLUP);
  pinMode(pin1, INPUT_PULLUP);

  //Serial.print("Attach ENC0A to ");
  //Serial.print(digitalPinToInterrupt(pin0));
  //Serial.println();

  //Serial.print("Attach ENC0B to ");
  //Serial.print(digitalPinToInterrupt(pin1));
  //Serial.println();

  attachInterrupt(pin0, update, CHANGE);
  attachInterrupt(pin1, update, CHANGE);
  pin0_mask = digitalPinToBitMask(pin0);
  pin1_mask = digitalPinToBitMask(pin1);
  pin0_port = portInputRegister(digitalPinToPort(pin0));
  pin1_port = portInputRegister(digitalPinToPort(pin1));
  //Serial.println("Done setup interface (native_pins). ");
}

template< char pin0, char pin1> void lamb::encoders::interfaces::native_pins<pin0, pin1>::update() {
#ifdef __AVR__
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
#endif
    //	//Serial.println("Update... ");
    unsigned char current = (!!(*pin0_port & pin0_mask))<<1 | !!(*pin1_port & pin1_mask);
    ////Serial.print("Current = ");
    ////Serial.print(current, DEC);
    ////Serial.println();
    state->update(current);
    ////Serial.println("Done update.");
#ifdef __AVR__
  }
#endif
}

////////////////////////////////////////////////////////////////////////////////
// lamb::encoders::whole_mcp<> definitions
////////////////////////////////////////////////////////////////////////////////
#if defined(__AVR_ARCH__) && ! defined(__AVR_ATtiny85__)
template <uint8_t irq_pin, uint8_t i2c_addr, typename state_t> Adafruit_MCP23017 *lamb::encoders::whole_mcp<irq_pin, i2c_addr, state_t>::mcp = 0;
template <uint8_t irq_pin, uint8_t i2c_addr, typename state_t> state_t lamb::encoders::whole_mcp<irq_pin, i2c_addr, state_t>::states[8];
template <uint8_t irq_pin, uint8_t i2c_addr, typename state_t> volatile bool lamb::encoders::whole_mcp<irq_pin, i2c_addr, state_t>::pending = false;

template <uint8_t irq_pin, uint8_t i2c_addr, typename state_t>
typename lamb::encoders::whole_mcp<irq_pin, i2c_addr, state_t>::state_type &
lamb::encoders::whole_mcp<irq_pin, i2c_addr, state_t>::state(uint8_t ix) {
  return states[ix];
}

template <uint8_t irq_pin, uint8_t i2c_addr, typename state_t>
void lamb::encoders::whole_mcp<irq_pin, i2c_addr, state_t>::setup(Adafruit_MCP23017 * mcp_, bool attach) {
  mcp = mcp_;

  pinMode(irq_pin, INPUT);

  for (auto x = 0; x < 16; x++) {
    mcp->pinMode(x, INPUT);
    mcp->pullUp(x, HIGH);
    mcp->setupInterruptPin(x, CHANGE);
  }

  mcp->setupInterrupts(true, false, LOW);
  mcp->readGPIOAB();
  if (attach)
    attachInterrupt(irq_pin, mcp_irq, FALLING);
  poll(true);
}

template <uint8_t irq_pin, uint8_t i2c_addr, typename state_t>
bool lamb::encoders::whole_mcp<irq_pin, i2c_addr, state_t>::poll(bool force) {
  if (! (pending || force))
    return false;

  typename state_t::value_type gpio = mcp->readGPIOAB();
  uint16_t mask = 0b1100000000000000;
  uint8_t shift = 14;

  for (uint8_t ix = 0; ix < 8; ix++) {
    uint8_t tmp = (gpio & mask) >> shift;
    states[ix].update(tmp);
    mask >>= 2;
    shift -= 2;
  }

  pending = false;
  return true;
}

template <uint8_t irq_pin, uint8_t i2c_addr, typename state_t>
void lamb::encoders::whole_mcp<irq_pin, i2c_addr, state_t>::mcp_irq() {
  pending = true;
}
#endif
////////////////////////////////////////////////////////////////////////////////
// lamb::encoders::uint<> definitions
////////////////////////////////////////////////////////////////////////////////

template <char pin0, char pin1, char bits> lamb::encoders::states::uint<bits> lamb::encoders::uint<pin0, pin1, bits>::state;

template <char pin0, char pin1, char bits>
bool lamb::encoders::uint<pin0, pin1, bits>::flag() {
  return state.flagged;
}

template <char pin0, char pin1, char bits>
void lamb::encoders::uint<pin0, pin1, bits>::set_flag(bool f) {
  state.flagged = f;
}

template <char pin0, char pin1, char bits>
uint16_t lamb::encoders::uint<pin0, pin1, bits>::value() {
  return state.value();
}

template <char pin0, char pin1, char bits>
void lamb::encoders::uint<pin0, pin1, bits>::set_value(uint16_t v) {
  return state.set_value(v);
}

template <char pin0, char pin1, char bits>
void lamb::encoders::uint<pin0, pin1, bits>::setup() {
  lamb::encoders::interfaces::native_pins<pin0, pin1> tmp;
  tmp.setup(&state);
}

////////////////////////////////////////////////////////////////////////////////
// lamb::encoders::func_ptr<> definitions
////////////////////////////////////////////////////////////////////////////////

template <char pin0, char pin1> lamb::encoders::states::func_ptr lamb::encoders::func_ptr<pin0, pin1>::state;

template <char pin0, char pin1>
void lamb::encoders::func_ptr<pin0, pin1>::setup(void(*up)(), void(*down)())
{
  lamb::encoders::interfaces::native_pins<pin0, pin1> tmp;
  tmp.setup(&state);

  state.up_func = up;
  state.down_func = down;
}

////////////////////////////////////////////////////////////////////////////////
#endif
