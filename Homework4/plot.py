#!/opt/homebrew/bin/python3

import pandas as pd
import matplotlib.pyplot as plot

df = pd.read_csv("wall_time.csv").groupby('n').agg({'bf': 'mean', 'bb': 'mean'}).reset_index()

fig, ax = plot.subplots(2, 1)
fig.suptitle("110062219")

ax[0].axis('tight')
ax[0].axis('off')
ax[0].table(tuple((n, f"{bf:.1f}", f"{bb:.3f}") for n, bf, bb in zip(df['n'], df["bf"], df["bb"])), colLabels=("n", "Brute Force", "Branch & Bound"), edges="B", loc="center")

ax[1].plot(df['n'], df["bf"], label="Brute Force")
ax[1].plot(df['n'], df["bb"], label="Branch & Bound")
ax[1].legend()
ax[1].set_xlabel("n")
ax[1].set_ylabel("Average Wall Time [μs] (log scale)")
ax[1].set_yscale("log")

fig.savefig("plot.png")
