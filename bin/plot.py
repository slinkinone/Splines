#/bin/python

import sys
import matplotlib.pyplot as plt

#def add_plot():


if __name__ == "__main__":
	colors = "bgrcmykw"
	color_index = 0
	for file_name in sys.argv[1:]:
		x_arr = []
		y_arr = []
		
		plot_label = ('.').join(file_name.split('.')[:-1])
		lines = [line.rstrip('\n') for line in open(file_name)]
		for point in lines:
			split_point = point.split(",")
			x_arr.append(float(split_point[0]))
			y_arr.append(float(split_point[1]))

		color = ""
		if color_index == 0:
			color = colors[color_index] + "o"
		else:
			color = colors[color_index] + "-"

		print(file_name)
		plt.plot(x_arr, y_arr, color, label=plot_label, linewidth=2)
		color_index += 1

	plt.legend(bbox_to_anchor=(1.04,1), loc="upper left")
	plt.show()
	sys.exit()