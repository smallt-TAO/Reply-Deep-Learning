## Training

- Download the 16x16 and 28x28 GridWorld datasets from the [author's repository](https://github.com/avivt/VIN/tree/master/data). This repository contains the 8x8 GridWorld dataset for convenience and its small size.

```
# Runs the 8x8 Gridworld with default parameters
python3 train.py
```

The 8x8 GridWorld model converges in under 30 epochs with about ~98.5% accuracy. The paper lists that it should be around 99.6% and I was able to reproduce this with the Theano code. Results for 16x16 and 28x28 can be seen [here](https://github.com/TheAbhiKumar/tensorflow-value-iteration-networks/issues/6)

## Dependencies
* Python >= 3.6
* TensorFlow >= 1.0
* SciPy >= 0.18.1 (to load the data)
