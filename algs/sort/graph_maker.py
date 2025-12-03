import matplotlib.pyplot as plt

plt.style.use("dark_background")

languages = ["C", "C++(ptr)", "C++(vector)", "Java", "JS", "Python", "Dart-AOT", "Dart-JIT"]

quick_impl = [2.75, 2.8, 3.25, 3.7, 5.4, 155, 21, 3.8]
merge_sort = [3.9, 3.9, 4.3, 6.5, 11.8, 490, 38, 5.9]
built_in =   [8.4, 2.95, 3.0, 3.65, 16.7, 10.3, 16.6, 10.5]

x = range(len(languages))
width = 0.25

plt.figure(figsize=(14,9))
bars1 = plt.bar([i-width for i in x], quick_impl, width=width, label="Custom QuickSort")
bars2 = plt.bar(x, merge_sort, width=width, label="Custom Merge Sort")
bars3 = plt.bar([i+width for i in x], built_in, width=width, label="Built-in Sort")

for bars in [bars1, bars2, bars3]:
    for bar in bars:
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width()/2, height, f'{height:.2f}', 
                 ha='center', va='bottom', fontsize=9, color="white")

plt.xticks(x, languages)
plt.ylabel("Time (seconds, log scale)")
plt.title("Sorting Performance Comparison by Language (Quick / Merge / Built-in)")
plt.yscale("log")  # Log scale to compare large values
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.show()

