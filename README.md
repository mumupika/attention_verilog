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

## QuestaSim Simulation Display

<img width="561" alt="Screenshot 2024-12-30 at 13 49 58" src="https://github.com/user-attachments/assets/805d0585-0493-41ce-9c55-ace81c2bdb6b" />
