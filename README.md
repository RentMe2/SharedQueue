
# SharedQueue
[![CircleCI](https://circleci.com/gh/RentMe2/SharedQueue.svg?style=svg)](https://github.com/RentMe2/SharedQueue)
<br />
<br />

[![Coverage Badge](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/MuhammadMoeedUllah/52019294b0eaaae8927f305e7c1b7052/raw/SharedQueue__heads_main.json)]
<br />
<br />

![example workflow](https://github.com/RentMe2/SharedQueue/actions/workflows/test_coverage.yml/badge.svg)
<br />

A simple library that implements a thread safe queue for multiple consumers and multiple producers.  

To run the project use following steps
```
mkdir build
cd build
cmake ..
```

This will setup the project. Now let's build the executable as following
```
make 
```

Now run the executable. 
```
./sharedQueue
```

That's it. In future changes I will be adding testing and logging using some public libraries
for exmple spdlog and Catch2 for unit testing.



