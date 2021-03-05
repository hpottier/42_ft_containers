# 42_ft_containers
Recoding std::list, std::vector, std::map, std::stack and std::queue without a single call to the stl as project for the 42Paris coding school.
To call it, use the namespace ft:: instead of std:: like this:
```
ft::list<int> lst;
```

The main and bash script are here to test my implementation against the std.

## Usage
```
>$ ./tester
```
### To only compile the main with my implementation
```
>$ g++ -D TFT main.cpp
```
### To only compile the main with the std
```
>$ g++ main.cpp
```
