#include "config.h"

using namespace std;

float feature_map1[24 * 24 * 20];
float max_pool1[12 * 12 * 20];
float feature_map2[8 * 8 * 50];
float max_pool2[4 * 4 * 50];
float ip1[500];
float tanh1[500];
float ip2[10];
