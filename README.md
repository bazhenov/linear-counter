# Linear counter

Simlple CLI utility for making efficient estimate of nunber of unique strings in the given stream. Algorithm doesn't need to store and sort all of the given entries and has space complexity of O(1) and time complexity of O(N) which is way faster than using ` | sort | uniq | wc -l`.


## Installation

On the macos:

```
$ brew tap bazhenov/tap
$ brew install linear-counter
```

## Using

```
$ cat "very_large_file" | linear-counter
```
