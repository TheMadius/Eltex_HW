#ifndef PLUGIN_
#define PLUGIN_

enum type_arg {
  TYPE_INT,
  TYPR_DOUBLE,
  TYPR_FLOAT,
  TYPE_VOID
};

struct setting_plugin {
  int count_arg;
  enum type_arg type_return;
};

#endif //PLUGIN_