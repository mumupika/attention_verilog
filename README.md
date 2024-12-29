# Attention Verilog Homework

This repository is for completing an easy self-attention model by verilog.
~~I want stars But no one gives stars to me QAQ~~

## Golden model

For Golden model, this is for checking the results of the hardware output. To see the results, do as follows:

```bash
cd golden_model
make && ./main 1 2 3 # (query: 1, key: 2, value: 3)
# or using:
# make && ./main 1 (seed will be: 1 2 3)
# or using:
# make && ./main (default seed: 1 2 3)
make clean
```
