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
	int img_size = image_size.first * image_size.second;
	int i_size = num_features * img_size; // size of total input
	int f_size = num_features * filter_size.first * filter_size.second; // size of 1 filter

	for (int i = 0; i < num_filters; i++) { // i = filter number
		for (int j = 0; j < image_size.first - filter_size.first + 1; j++) { // j = height
			for (int k = 0; k < image_size.second - filter_size.second + 1; k++) { // k = width

				int sum = bias[i];

				for (int a = 0; a < num_features; a++) {
					for (int b = 0; b < filter_size.first; b++) {
						for (int c = 0; c < filter_size.second; c++) {
							sum += image[a*img_size + (j+b)*image_size.second + (k+c)] * filter[i*f_size + a*filter_size.first*filter_size.second + b*filter_size.second + c];
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

	int img_size = image_size.first * image_size.second;

	for (int i = 0; i < channel; i++) { // i = 현재 채널(depth)
		for (int j = 0; j < image_size.first - max_pool_size.first + 1; j++) { // j = height
			for (int k = 0; k < image_size.second - max_pool_size.second + 1; k++) { // k = width
				
				int maxi = 0;
				
				for (int a = j; a < j + max_pool_size.first; a++) {
					for (int b = k; b < k + max_pool_size.second; b++) {
						maxi = max(maxi, image[i * img_size + a * image_size.second + b]);
					}
				}
				max_pool[i * (image_size.first - max_pool_size.first + 1) * (image_size.second - max_pool_size.second + 1) + j * (image_size.second - max_pool_size.second + 1) + k] = maxi;

			}
		}
	}
}

void ReLu(w_t *image,
		  pair<uint32_t, uint32_t> image_size,
		  uint32_t num_output,												
		  w_t *output) {
		//FIXME

	int img_size = image_size.first * image_size.second;

	for (int i = 0; i < i_size; i++) {
		output[img_size * i + j] = image[img_size * i + j] ? image[img_size * i + j] : 0;
	}
}

void TanH(w_t *image, 												// input image
		  pair<uint32_t, uint32_t> image_size,						// input image size
		  uint32_t num_output,										// number of output feature
		  w_t *output){												// output
		//FIXME

	int img_size = image_size.first * image_size.second;
	int i_size = num_output * img_size; // size of total input

	for (int i = 0; i < i_size; i++) {
		output[i] = tanh(image[i]);
	}
}

void ip(w_t *input, pair<uint32_t, uint32_t> input_size,			// input image
		uint32_t num_features,										// number of 1 input's features
		w_t *weight,												// weights
		w_t *bias,													// bias
		uint32_t num_output,										// number of output neurons
		w_t *output){												// output
		//FIXME

	int img_size = input_size.first * input_size.second;
	int i_size = num_features * img_size; // size of total input

	for (int out = 0; out < num_output; out++) { // out = 현재 output#
		
		int sum = bias[out];
		for (int i = 0; i < i_size; i++) { 
			sum += input[i] * weight[out * i_size + i];
		}
		output[out] = sum;

	}
}

/*
void accuracy(uint32_t iter,
							uint32_t *label,
							w_t *output){
		//FIXME
}
*/
