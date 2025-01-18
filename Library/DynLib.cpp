void f1(char*& s) {
    long long size = 0;
    while(s[size]!='\0')size++;
    // сортировка
    for(int i=0; i<size; i++){
        for(int j=0; j<size-1-i; j++){
            if(s[j] < s[j+1]){
              char t = s[j];
              s[j] = s[j+1];
              s[j+1] = t;
            }
        }
    }
    if(size==1){
        s = new char[2];
        s[0] = 'K';
        s[1] = 'B';
        size = 2;
        return;
    }
    char* sub_s = new char[size];
    for (long long i = 0; i < size; ++i) {
        sub_s[i] = s[i];
    }
    delete[] s;
    long long prev_size = size;
    
    s = new char[size = (size + (size >> 1) + (size & 1))]; 
    // замена чётных элементов на "КВ"
    for (long long i = 0, j = 1; i+2<size && j<prev_size; j += 2, i += 3) {
        s[i] = 'K';
        s[i + 1] = 'B';
        s[i + 2] = sub_s[j];
    }
    if(prev_size&1){
        s[size-2] = 'K';
        s[size-1] = 'B';
    }
    s[size] = '\0';
    delete[] sub_s;
}

long long f2(char *&s) {
    long long size = 0;
    while(s[size]!='\0')size++;
    if (size == 0)return 0;

    long long S = 0;  // Сумма
    char t;
    long long i = 0;
    long long N = 0;
    while (i < size) {
        t = s[i];
        N = 0;
        while (i < size && t >= '0' && t <= '9') {
            N = N * 10 + t - '0';
            i++;
            t = s[i];
        }
        i++;
        S = S + N;
    }
    return S;
}

bool f3(char *&s) {
    long long size=0;
    while(s[size]!='\0')size++;
    return ((!(size&31)) && (size>>5));
}
