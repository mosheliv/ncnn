// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "layer/rnn.h"
#include "testutil.h"

static int test_rnn(const ncnn::Mat& a, int outch, int direction)
{
    int input_size = a.w * a.h * a.c;
    int num_directions = direction == 2 ? 2 : 1;

    ncnn::ParamDict pd;
    pd.set(0, outch);
    pd.set(1, outch * input_size * num_directions);
    pd.set(2, direction);

    std::vector<ncnn::Mat> weights(3);
    weights[0] = RandomMat(outch * input_size * num_directions);
    weights[1] = RandomMat(outch * num_directions);
    weights[2] = RandomMat(outch * outch * num_directions);

    int ret = test_layer<ncnn::RNN>("RNN", pd, weights, a);
    if (ret != 0)
    {
        fprintf(stderr, "test_rnn failed a.dims=%d a=(%d %d %d) outch=%d, direction = %d \n", a.dims, a.w, a.h, a.c, outch, direction);
    }

    return ret;
}

int test_rnn_layer_with_hidden(const ncnn::Mat& a, int outch, int direction)
{
    int input_size = a.w * a.h * a.c;

    ncnn::ParamDict pd;
    pd.set(0, outch);
    pd.set(1, outch * input_size);
    pd.set(2, direction);

    std::vector<ncnn::Mat> weights(3);
    weights[0] = RandomMat(outch * input_size);
    weights[1] = RandomMat(outch);
    weights[2] = RandomMat(outch * outch);

    // initial hidden state
    ncnn::Mat hidden = RandomMat(outch);

    std::vector<ncnn::Mat> as(2);
    as[0] = a;
    as[1] = hidden;

    int ret = test_layer<ncnn::RNN>("RNN", pd, weights, as, 2);
    if (ret != 0)
    {
        fprintf(stderr, "test_rnn_layer_with_hidden failed a.dims=%d a=(%d %d %d) outch=%d, direction = %d \n", a.dims, a.w, a.h, a.c, outch, direction);
    }

    return ret;
}

static int test_rnn_0()
{
    return 0
           || test_rnn(RandomMat(4, 1), 2, 2)
           || test_rnn(RandomMat(8, 2), 2, 2)
           || test_rnn(RandomMat(16, 8), 7, 2)
           || test_rnn(RandomMat(17, 8), 8, 2)
           || test_rnn(RandomMat(19, 15), 8, 2)
           || test_rnn(RandomMat(5, 16), 16, 2)
           || test_rnn(RandomMat(3, 16), 8, 2)
           || test_rnn(RandomMat(8, 16), 16, 2)
           || test_rnn(RandomMat(2, 5), 17, 2);
}

static int test_rnn_1()
{
    return 0
           || test_rnn_layer_with_hidden(RandomMat(4, 4), 1, 1)
           || test_rnn_layer_with_hidden(RandomMat(8, 2), 2, 1)
           || test_rnn_layer_with_hidden(RandomMat(16, 8), 7, 1)
           || test_rnn_layer_with_hidden(RandomMat(17, 8), 8, 1)
           || test_rnn_layer_with_hidden(RandomMat(19, 15), 8, 1)
           || test_rnn_layer_with_hidden(RandomMat(5, 16), 16, 1)
           || test_rnn_layer_with_hidden(RandomMat(3, 16), 8, 1)
           || test_rnn_layer_with_hidden(RandomMat(2, 5), 99, 1)
           || test_rnn_layer_with_hidden(RandomMat(4, 2), 1, 0)
           || test_rnn_layer_with_hidden(RandomMat(8, 2), 2, 0)
           || test_rnn_layer_with_hidden(RandomMat(16, 8), 7, 0)
           || test_rnn_layer_with_hidden(RandomMat(17, 8), 8, 0)
           || test_rnn_layer_with_hidden(RandomMat(19, 15), 8, 0)
           || test_rnn_layer_with_hidden(RandomMat(5, 16), 16, 0)
           || test_rnn_layer_with_hidden(RandomMat(3, 16), 8, 0)
           || test_rnn_layer_with_hidden(RandomMat(2, 5), 17, 0);
}

static int test_rnn_2()
{
    return 0
           || test_rnn(RandomMat(4, 1), 1, 0)
           || test_rnn(RandomMat(8, 2), 2, 0)
           || test_rnn(RandomMat(16, 8), 7, 0)
           || test_rnn(RandomMat(17, 8), 8, 0)
           || test_rnn(RandomMat(19, 15), 8, 0)
           || test_rnn(RandomMat(5, 16), 16, 0)
           || test_rnn(RandomMat(3, 16), 8, 0)
           || test_rnn(RandomMat(8, 16), 16, 0)
           || test_rnn(RandomMat(2, 5), 17, 0);
}

static int test_rnn_3()
{
    return 0
           || test_rnn(RandomMat(4, 1), 1, 1)
           || test_rnn(RandomMat(8, 2), 2, 1)
           || test_rnn(RandomMat(16, 8), 7, 1)
           || test_rnn(RandomMat(17, 8), 8, 1)
           || test_rnn(RandomMat(19, 15), 8, 1)
           || test_rnn(RandomMat(5, 16), 16, 1)
           || test_rnn(RandomMat(3, 16), 8, 1)
           || test_rnn(RandomMat(8, 16), 16, 1)
           || test_rnn(RandomMat(2, 5), 17, 1);
}

int main()
{
    SRAND(7767517);
    return test_rnn_0() || test_rnn_1() || test_rnn_2() || test_rnn_3();
}
