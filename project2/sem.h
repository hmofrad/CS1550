struct cs1550_sem {
  int value;
  //struct list_head queue;
  struct my_queue* head;
  struct my_queue* tail;
};
