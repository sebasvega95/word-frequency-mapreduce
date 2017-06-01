# Word frequency MapReduce
Count the occurrences of each word in a text file concurrently (Partitioning the text and assigning each partition to a *mapper*, then collecting all results in *reducers*) 

## Dependencies

- [ZeroMQ](http://zeromq.org/)
- [zmqpp](https://github.com/zeromq/zmqpp)
- [JSON for Modern C++](https://github.com/nlohmann/json) (Included in `lib/`)

## Usage

To compile simply type in a terminal

```bash
 make
```

The file `config.json` contains information about mappers, reducers and the partitioner. There's [an example](https://github.com/sebasvega95/word-frequency-mapreduce/blob/master/config.json) local configuration in this repository.

To run, do

- `./partitioner.out text`
- `./mapper.out node_name`
- `./reducer.out node_name`

where

- `text` is the file for calculating the word count
- `node_name` is the name of a node according to `config.json`
