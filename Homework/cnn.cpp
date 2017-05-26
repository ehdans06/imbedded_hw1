/*TODO: for loop을 최대한 줄여보기!*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>

#include "cnn.h"
#include "config.h"

using namespace std;
w_t test_image[1000][1 * 28 * 28];

void conv(w_t *image,								    // input image
	pair<uint32_t, uint32_t> image_size,			// input image size
	uint32_t num_features,						// number of features in input = channel
	w_t *filter,								    // convolution filter source
	w_t *bias,			                        // convolution bias source
	uint32_t num_filters,				            // number of output 
	w_t *feature_map,							    // output image
	pair<uint32_t, uint32_t> filter_size,			// filter size
	int32_t pad,								    // number of padding
	uint32_t stride) {						    // number of stride
												//FIXME

												// padding은 고려하지 않음
	uint32_t img_size = image_size.first * image_size.second;
	uint32_t f_size = num_features * filter_size.first * filter_size.second; // size of 1 filter

	for (uint32_t i = 0; i < num_filters; i++) { // i = filter number
		for (uint32_t j = 0; j < image_size.first - filter_size.first + 1; j += stride) { // j = height
			for (uint32_t k = 0; k < image_size.second - filter_size.second + 1; k += stride) { // k = width

				w_t sum = bias[i];

				for (uint32_t a = 0; a < num_features; a++) {
					for (uint32_t b = 0; b < filter_size.first; b++) {
						for (uint32_t c = 0; c < filter_size.second; c++) {
							sum += image[a*img_size + (j + b)*image_size.second + (k + c)] * filter[i*f_size + a*filter_size.first*filter_size.second + b*filter_size.second + c];
						}
					}
				}
				feature_map[i * (image_size.first - filter_size.first + 1) * (image_size.second - filter_size.second + 1) + j * (image_size.second - filter_size.second + 1) + k] = sum;

			}
		}
	}
}

void max_pool(w_t *image,									// input image
	pair<uint32_t, uint32_t> image_size,			// input image size
	uint32_t channel,								// number of features in input image = channel
	pair<uint32_t, uint32_t> max_pool_size,		// pooling size
	uint32_t stride,								// strdie
	w_t *max_pool) {								// output image
													//FIXME

	uint32_t img_size = image_size.first * image_size.second;

	for (uint32_t i = 0; i < channel; i++) { // i = 현재 채널(depth)
		for (uint32_t j = 0; j < image_size.first - max_pool_size.first + 1; j += stride) { // j = height
			for (uint32_t k = 0; k < image_size.second - max_pool_size.second + 1; k += stride) { // k = width

				w_t maxi = 0;

				for (uint32_t a = 0; a < max_pool_size.first; a++) {
					for (uint32_t b = 0; b < max_pool_size.second; b++) {
						maxi = max(maxi, image[i * img_size + (j + a) * image_size.second + (k + b)]);
					}
				}
				max_pool[i * (image_size.first / stride) * (image_size.second / stride) + j / stride * (image_size.second / stride) + k / stride] = maxi;

			}
		}
	}
}

void ReLu(w_t *image,
	pair<uint32_t, uint32_t> image_size,
	uint32_t num_output,
	w_t *output) {
	//FIXME

	uint32_t img_size = image_size.first * image_size.second;
	uint32_t i_size = num_output * img_size; // size of total input

	for (uint32_t i = 0; i < i_size; i++) {
		output[i] = (image[i] > 0) ? image[i] : 0;
	}
}

void TanH(w_t *image, 												// input image
	pair<uint32_t, uint32_t> image_size,						// input image size
	uint32_t num_output,										// number of output feature
	w_t *output) {												// output
																//FIXME

	uint32_t img_size = image_size.first * image_size.second;
	uint32_t i_size = num_output * img_size; // size of total input

	for (uint32_t i = 0; i < i_size; i++) {
		output[i] = tanh(image[i]);
	}
}

void ip(w_t *input, pair<uint32_t, uint32_t> input_size,			// input image
	uint32_t num_features,										// number of 1 input's features
	w_t *weight,												// weights
	w_t *bias,													// bias
	uint32_t num_output,										// number of output neurons
	w_t *output) {												// output
																//FIXME

	uint32_t img_size = input_size.first * input_size.second;
	uint32_t i_size = num_features * img_size; // size of total input

	for (uint32_t out = 0; out < num_output; out++) { // out = 현재 output#

		w_t sum = bias[out];
		for (uint32_t i = 0; i < i_size; i++) {
			sum += input[i] * weight[out * i_size + i];
		}
		output[out] = sum;

	}
}


void accuracy(uint32_t iter,
	uint32_t *label,
	w_t *output) {
	//FIXME
	w_t max_val = -9999;
	uint32_t predict = 0;

	for (uint32_t i = 0; i < 10; i++) {
		predict = (max_val < output[i]) ? i : predict;
	}

	if (predict == label[iter]) printf("test %d: correct\t(label: %d, prediction: %d)\n", iter, label[iter], predict);
	else printf("test %d: incorrect\t(label: %d, prediction: %d)\n", iter, label[iter], predict);
}

