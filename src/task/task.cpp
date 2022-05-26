#include "../../include/task/task.h"

char lamb::task::last_id = 0;

void lamb::task::describe() const {
#ifdef LAMBOS_TASK_DEBUG
  Serial.print("Construct #");
  Serial.print(id, DEC);
  Serial.print(" interv ");
  Serial.print(interval, DEC);
  Serial.print(" last_ran ");
  Serial.print(last_ran, DEC);
  Serial.println();
#endif
}

lamb::task::task(
  void(*_work)(),
  unsigned long _interval,
  volatile bool * _flag
) :
  last_ran(0),
  interval(_interval),
  flag(_flag),
  work(_work)
{
  id = last_id++;
  describe();
}

lamb::task::task(
  void(*_work)(),
  volatile bool * _flag,
  unsigned long _interval
) :
  last_ran(0),
  interval(_interval),
  flag(_flag),
  work(_work)
{
  id = last_id++;
  describe();
}

lamb::task::task(
  void(*_work)()
) :
  last_ran(0),
  interval(0),
  flag(0),
  work(_work)
{
  id = last_id++;
  describe();
}

bool lamb::task::operator()(unsigned long now) {
  static unsigned long delta;
  delta = now - last_ran;

  if ((0 == flag || (*flag)) &&
       delta >= interval
       ) {

    last_ran = now;

#ifdef LAMBOS_TASK_DEBUG
    Serial.print("Exec ");
    describe();
#endif

    work();

    if (0 != flag)
      (*flag) = false;

    return true;
  }
  else
    return false;
}
