#ifndef LAMB_LIGHT_BUFFER
#define LAMB_LIGHT_BUFFER

#define declare_light_buffer_256(t, name) t name[256]; \
uint8_t name ## _write_ix = 0; \
uint8_t name ## _read_ix = 0; \
uint8_t name ## _count = 0 

#define light_buffer_256_read(b) b[b ## _count--, b ## _read_ix++]

#define light_buffer_256_peek(b) b[b ## _read_ix]

#define light_buffer_256_write(b, v) b[ b ## _count++, b ## _write_ix++] = v

#define light_buffer_256_writable(b) (b ## _count < 255)

#define light_buffer_256_readable(b) (b ## _count)

#define declare_light_buffer(t, len, name) \
t name[len]; \
typedef t (name ## _type); \
uint8_t name ## _write_ix = 0; \
uint8_t name ## _read_ix = 0; \
uint8_t name ## _count = 0; \
static const uint8_t name ## _length = len

#define declare_static_light_buffer(t, len, name) \
  static t name[len];                             \
  typedef t (name ## _type);                      \
  static uint8_t name ## _write_ix;               \
  static uint8_t name ## _read_ix;                \
  static uint8_t name ## _count;                  \
  static const uint8_t name ## _length = len

#define define_static_light_buffer(owner_t, name, len)   \
  owner_t::(name ## _type) owner_t::name[len] = { 0 }    \
  uint8_t owner_t::name ## _write_ix = 0;                \
  uint8_t owner_t::name ## _read_ix = 0;                 \
  uint8_t owner_t::name ## _count = 0

#define declare_dynamic_light_buffer(t, name) t * name; \
typedef t (name ## _type); \
uint8_t name ## _write_ix = 0; \
uint8_t name ## _read_ix = 0; \
uint8_t name ## _count = 0; \
uint8_t name ## _length = 0

// v This is primarily meant for cases where objects each require diferent sized buffers.
//   It's mainly meant to be used in constructors, it' not really meant for resizing during
//   the object's lifetime... watch out for what happens to the indexes if you're gonna use it
//   that way, especially if you're reducing it's size.

#define dynamic_light_buffer_resize(t, name, count) (name ## _type) * name; \
(name ## _length) = count; \
name = (t *) malloc((name ## _length) * sizeof(t));

#define light_buffer_available(b) ((b ## _length) - (b ## _count))

#define light_buffer_read(b)     b[b ## _read_ix %= b ## _length, b ## _count--, b ## _read_ix++]
#define light_buffer_peek(b)     b[b ## _read_ix]

#define light_buffer_write(b, v) b[b ## _write_ix %= b ## _length,  b ## _count++, b ## _write_ix++] = v

#define light_buffer_clear(b) b ## _write_ix = 0; b ## _read_ix = 0; b ##_count = 0

#define light_buffer_writable(b) ((b ## _count) < (b ## _length))

#define light_buffer_readable(b) (b ## _count)

#endif
