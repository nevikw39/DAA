#!/opt/homebrew/bin/python3

import pandas as pd
import matplotlib.pyplot as plot

df = pd.read_csv("wall_time.csv").groupby('n').agg({'qs': 'mean', 'pns': 'mean'}).reset_index()

fig, ax = plot.subplots(1, 2, figsize=plot.figaspect(1 / 2.5))
fig.suptitle("110062219 110062238")

ax[0].axis('tight')
ax[0].axis('off')
ax[0].table(tuple((f"{n:.1e}", f"{qs:.2f}", f"{pns:.2f}") for n, qs, pns in zip(df['n'], df["qs"], df["pns"])), colLabels=("n", "Quicksort", "Prune & Search"), edges="B", loc="center")

ax[1].plot(df['n'], df["qs"], label="Quicksort")
ax[1].plot(df['n'], df["pns"], label="Prune & Search")
ax[1].legend()
ax[1].set_xlabel("n")
ax[1].set_ylabel("Average Wall Time [ms] (log scale)")
ax[1].set_yscale("log")

fig.savefig("plot.png")
