#include <iostream>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>
#include "DynLib.h"

char *buf = NULL;  // общий буфер
pthread_mutex_t mutex;  // мьютекс потоков
pthread_cond_t cond;

bool ready = false;
bool port_flag = false;
void *t1(void *arg){    // функция для потока 1
   while(!port_flag)sleep(1);
  while(1){
    pthread_mutex_lock(&mutex);
    if (ready == 1)
    {
      pthread_mutex_unlock(&mutex);
      continue;
    }
    ready = 0;
    char *t;
    buf = new char[128];
    bool flag_char = false;
    bool flag_size = false;
    int size=0;
    while( !(flag_char && flag_size)){
      flag_char = flag_size = true;
      std::cout<<"Enter string: ";
      t = new char;
      std::cin>>t;
      size=0;
      // проверка на размер строки (<=64) и на отсутствие в ней символов, кроме цифр
      while(t[size]!='\0'){
        if(t[size] <'0' || t[size] > '9'){ flag_char = false; delete[] t; break;}
        if( (size >> 6) & (size&1)){ flag_size = false; delete[] t; break; }
        size++;
      }
    }
    f1(t);
    for(size=0; t[size]!='\0'; buf[size] = t[size], size++);
    buf[size] = '\0';
    delete[] t; 
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  return NULL;
}
void *t2(void *arg){      
    std::cout<<"Enter servers port: ";
    int server_port;
    std::cin>>server_port;
    pthread_cond_signal(&cond);
    port_flag = true;
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;    // семейство адресов IPv4
    serverAddress.sin_port = htons(server_port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    while(1){
      pthread_mutex_lock(&mutex);
      while (ready == 0)
      {
        pthread_cond_wait(&cond, &mutex);
        int size=0;
        for(size; buf[size]!='\0'; std::cout<<buf[size], size++);
        int S = f2(buf);
        char *tosend = new char[10]; // строка от отправку программе 2 (будет содержать результат f2())
        int i;
        int tosend_size=0;
        if(S == 0){tosend[0] = '0'; tosend_size = 1;}
        else
        {
          for(i=0; S>0; tosend[i] = S%10 + 48, S/=10, i++);
          int tosend_size = i;
          tosend[i] = '\0';
          for(--i; i>=tosend_size/2; i--){ 
            char t = tosend[i];
            tosend[i] = tosend[tosend_size-i-1];
            tosend[tosend_size-i-1] = t;
          }
        }
      // отправка результата f2() программе 2
      send(clientSocket, tosend, sizeof(tosend), 0);
      delete [] tosend;  
      delete[] buf;
    }
    ready = 1;
    pthread_mutex_unlock(&mutex);
    sleep(1);
  }
  return NULL;
}

int main() {
    pthread_t thread1, thread2;

  // Инициализация мьютекса и условия
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
  // Создание потоков
    pthread_create(&thread1, NULL, t1, NULL);
    pthread_create(&thread2, NULL, t2, NULL);
  // запуск потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
  // очистка переменных мьютекса и состояния
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
