#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT_SHOP 5
#define COUNT_BUYERS 3
#define COUNT_EMPLOYEE 1
#define TRUE 1

struct shop {
  pthread_mutex_t door;
  int resources;
  int id;
};

struct buyer {
  int requirement;
  int id;
};

struct employee {
  int id;
  int speed;
};

struct thread_arg_buy {
  struct shop *list_shop;
  struct buyer *buyer;
  int count_shop;
};

struct thread_arg_update {
  struct shop *list_shop;
  struct employee *employee;
  int count_shop;
};

struct buyer buyer_init(int id) {
  struct buyer buy;
  srand(time(NULL));
  buy.id = id;
  buy.requirement = 9000 + rand() % 1001;
  return buy;
}

struct shop shop_init(int id) {
  struct shop new_shop;
  srand(time(NULL));
  new_shop.id = id;
  new_shop.resources = 490 + rand() % 21;
  pthread_mutex_init(&(new_shop.door), NULL);
  return new_shop;
}

struct employee employee_init(int id) {
  struct employee new_employee;
  srand(time(NULL));
  new_employee.id = id;
  new_employee.speed = 490 + rand() % 21;
  return new_employee;
}

void *shoping(void *argv) {
  struct thread_arg_buy *setting = (struct thread_arg_buy *)argv;

  while (setting->buyer->requirement > 0) {
    printf("Покупатель %d проснулся. Потребность покуптеля: %d\n", setting->buyer->id, setting->buyer->requirement);
    for(int i = 0; i < setting->count_shop; ++i) {
      if (pthread_mutex_trylock(&(setting->list_shop[i].door)) == 0) {
        printf("Покупатель %d зашел в %d магазин. Запасы магазина: %d\n", setting->buyer->id, setting->list_shop[i].id, setting->list_shop[i].resources);
        if (setting->list_shop[i].resources != 0) {
          setting->buyer->requirement -= setting->list_shop[i].resources;
          if(setting->buyer->requirement < 0) {
            setting->list_shop[i].resources = setting->buyer->requirement * (-1);
            setting->buyer->requirement = 0;
          } else {
            setting->list_shop[i].resources = 0;
          }
          printf("Покупатель %d пополнил свои запасы в %d магазине. Потребность покуптеля: %d\n", setting->buyer->id, setting->list_shop[i].id, setting->buyer->requirement);
          pthread_mutex_unlock(&(setting->list_shop[i].door));
          break;
        } else {
          printf("Покупатель %d вышел из %d магазина.\n", setting->buyer->id, setting->list_shop[i].id);
          pthread_mutex_unlock(&(setting->list_shop[i].door));
        }
      }
    }
    if (setting->buyer->requirement <= 0) {
      break;
    }
    printf("Покупатель %d засыпает\n", setting->buyer->id);
    sleep(2);
  }
  printf("Покупатель %d утолил свою потребность\n", setting->buyer->id);
  return NULL;
}

void *update_shop(void *argv) {
  struct thread_arg_update *setting = (struct thread_arg_update *)argv;
  srand(time(NULL));

  printf("Работник %d начал работу\n", setting->employee->id);
  while (TRUE)  {
    for(int i = rand() % setting->count_shop; i < setting->count_shop; ++i) {
      if (pthread_mutex_trylock(&(setting->list_shop[i].door)) == 0) {
        printf("Работник %d зашел в %d магазин. Запасы магазина: %d\n", setting->employee->id, setting->list_shop[i].id, setting->list_shop[i].resources);
        setting->list_shop[i].resources += setting->employee->speed;
        printf("Работник %d пополнил запасы в %d магазине. Запасы магазина: %d\n", setting->employee->id, setting->list_shop[i].id, setting->list_shop[i].resources);
        pthread_mutex_unlock(&(setting->list_shop[i].door));
        break;
      }
    }
    sleep(1);
  }

  return NULL;
}

int main(void) {
  pthread_t threads_shop[COUNT_BUYERS];
  pthread_t threads_update[COUNT_BUYERS];
  struct buyer buyers[COUNT_BUYERS];
  struct employee employees[COUNT_EMPLOYEE];

  struct thread_arg_buy argv[COUNT_BUYERS];
  struct thread_arg_update arge[COUNT_EMPLOYEE];

  struct shop list_shop[COUNT_SHOP];

  for (int i = 0; i < COUNT_SHOP; ++i) {
    list_shop[i] = shop_init(i + 1);
  }
  for (int i = 0; i < COUNT_BUYERS; ++i) {
    buyers[i] = buyer_init(i + 1);
  }
  for (int i = 0; i < COUNT_EMPLOYEE; ++i) {
    employees[i] = employee_init(i + 1);
  }

  for (int i = 0; i < COUNT_BUYERS; ++i) {
    argv[i].buyer = &(buyers[i]);
    argv[i].list_shop = list_shop;
    argv[i].count_shop = COUNT_SHOP;

    pthread_create(&(threads_shop[i]),NULL, shoping, &(argv[i]));
  }

  for (int i = 0; i < COUNT_EMPLOYEE; ++i) {
    arge[i].employee = &(employees[i]);
    arge[i].list_shop = list_shop;
    arge[i].count_shop = COUNT_SHOP;

    pthread_create(&(threads_update[i]),NULL, update_shop, &(arge[i]));
    pthread_detach(threads_update[i]);
  }

  for (int i = 0; i < COUNT_BUYERS; ++i) {
    pthread_join(threads_shop[i], NULL);
  }
}
