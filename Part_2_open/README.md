# Compile

```
$ gcc -fPIC -Wall -shared -o intercept_open.so ./intercept_open.c -ldl
```

```
$ gcc -fPIC -Wall -shared -o malicious.so ./malicious.c -ldl
```