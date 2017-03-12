### Particle Swarm Optimization

Ada beberapa catatan untuk pengembangan:

1. Fitness function sebaiknya diabstraksi dalam fungsi dan tidak diketik di tiga tempat yang berbeda sehingga ketika merubah fungsi tidak perlu copy-paste di tiga tempat melainkan cukup mengganti satu fungsi.

2. Jika swarm (node/titik) yang lama tidak dihapus namun warna diganti dengan warna yang lebih muda, maka akan kelihatan jejak langkah. Coba lihat http://neoswarm.com/worms_0.html

3. Visualisasi bisa dikembangkan menjadi 3D (https://pythonprogramming.net/matplotlib-3d-scatterplot-tutorial/) dan juga ditambahkan panah (http://matplotlib.org/examples/pylab_examples/arrow_simple_demo.html) melambangkan vector kecepatan seperti gambar di halaman Wikipedia mengenai particle swarm.

4. Jika tidak mau menggunakan ffmpeg (ffmpeg -framerate 24 -i img%03d.png output.mp4) untuk membuat video bisa menggunakan JSAnimation dari https://github.com/jakevdp/JSAnimation

5. Baca paper mengenai Particle Swarm Optimization dan coba kembangkan rumus dasar. (lihat pso.pdf)