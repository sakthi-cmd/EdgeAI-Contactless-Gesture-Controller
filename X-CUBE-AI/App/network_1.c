/**
  ******************************************************************************
  * @file    network_1.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-07-04T15:07:33+0530
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network_1.h"
#include "network_1_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network_1
 
#undef AI_NETWORK_1_MODEL_SIGNATURE
#define AI_NETWORK_1_MODEL_SIGNATURE     "0x50e6902aa9eeb2af76342863d63b844f"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2026-07-04T15:07:33+0530"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_1_N_BATCHES
#define AI_NETWORK_1_N_BATCHES         (1)

static ai_ptr g_network_1_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network_1_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  input_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 30, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1920, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_output2_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1920, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_output2_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  _Gather_output_0_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  output_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 4, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_kernel_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_recurrent_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16384, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_initial_h_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_initial_c_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 64, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_peepholes_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 192, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_kernel_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16384, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_recurrent_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 16384, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  _Constant_output_0_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 1, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  output_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 256, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  output_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 4, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 448, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 448, AI_STATIC)

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  _Constant_output_0, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &_Constant_output_0_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  _Gather_output_0_output, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_Gather_output_0_output_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_bias, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_lstm_LSTM_1_output_0_bias_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_kernel, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 64, 256, 1, 1), AI_STRIDE_INIT(4, 4, 256, 65536, 65536),
  1, &_lstm_LSTM_1_output_0_kernel_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_output0, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 30), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_lstm_LSTM_1_output_0_output0_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_output1, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_lstm_LSTM_1_output_0_output1_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_output2, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_lstm_LSTM_1_output_0_output2_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_recurrent, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 64, 256, 1, 1), AI_STRIDE_INIT(4, 4, 256, 65536, 65536),
  1, &_lstm_LSTM_1_output_0_recurrent_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_scratch0, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 448, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1792, 1792),
  1, &_lstm_LSTM_1_output_0_scratch0_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_bias, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_lstm_LSTM_output_0_bias_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_initial_c, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_lstm_LSTM_output_0_initial_c_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_initial_h, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_lstm_LSTM_output_0_initial_h_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_kernel, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 256, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1024, 1024),
  1, &_lstm_LSTM_output_0_kernel_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_output0, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 30), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_lstm_LSTM_output_0_output0_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_output1, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_lstm_LSTM_output_0_output1_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_output2, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &_lstm_LSTM_output_0_output2_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_peepholes, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 192), AI_STRIDE_INIT(4, 4, 4, 768, 768),
  1, &_lstm_LSTM_output_0_peepholes_array, NULL)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_recurrent, AI_STATIC,
  17, 0x0,
  AI_SHAPE_INIT(4, 64, 256, 1, 1), AI_STRIDE_INIT(4, 4, 256, 65536, 65536),
  1, &_lstm_LSTM_output_0_recurrent_array, NULL)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  _lstm_LSTM_output_0_scratch0, AI_STATIC,
  18, 0x0,
  AI_SHAPE_INIT(4, 1, 448, 1, 1), AI_STRIDE_INIT(4, 4, 4, 1792, 1792),
  1, &_lstm_LSTM_output_0_scratch0_array, NULL)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  input_output, AI_STATIC,
  19, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 30), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &input_output_array, NULL)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  output_bias, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &output_bias_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  output_output, AI_STATIC,
  21, 0x0,
  AI_SHAPE_INIT(4, 1, 4, 1, 1), AI_STRIDE_INIT(4, 4, 4, 16, 16),
  1, &output_output_array, NULL)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  output_weights, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 64, 4, 1, 1), AI_STRIDE_INIT(4, 4, 256, 1024, 1024),
  1, &output_weights_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Gather_output_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &output_weights, &output_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output_layer, 51,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense,
  &output_chain,
  NULL, &output_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _Gather_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &_lstm_LSTM_1_output_0_output0, &_Constant_output_0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_Gather_output_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  _Gather_output_0_layer, 50,
  GATHER_TYPE, 0x0, NULL,
  gather, forward_gather,
  &_Gather_output_0_chain,
  NULL, &output_layer, AI_STATIC, 
  .axis = AI_SHAPE_HEIGHT, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_lstm_LSTM_output_0_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_lstm_LSTM_1_output_0_output0, &_lstm_LSTM_1_output_0_output1, &_lstm_LSTM_1_output_0_output2),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 9, &_lstm_LSTM_1_output_0_kernel, &_lstm_LSTM_1_output_0_recurrent, NULL, NULL, NULL, &_lstm_LSTM_1_output_0_bias, &_lstm_LSTM_output_0_initial_h, &_lstm_LSTM_output_0_initial_c, &_lstm_LSTM_output_0_peepholes),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_lstm_LSTM_1_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _lstm_LSTM_1_output_0_layer, 45,
  LSTM_TYPE, 0x0, NULL,
  lstm, forward_lstm,
  &_lstm_LSTM_1_output_0_chain,
  NULL, &_Gather_output_0_layer, AI_STATIC, 
  .n_units = 64, 
  .activation_nl = nl_func_tanh_array_f32, 
  .go_backwards = false, 
  .reverse_seq = false, 
  .return_state = true, 
  .out_nl = nl_func_tanh_array_f32, 
  .recurrent_nl = nl_func_sigmoid_array_f32, 
  .cell_clip = 3e+38, 
  .state = AI_HANDLE_PTR(NULL), 
  .init = AI_LAYER_FUNC(NULL), 
  .destroy = AI_LAYER_FUNC(NULL), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  _lstm_LSTM_output_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &_lstm_LSTM_output_0_output0, &_lstm_LSTM_output_0_output1, &_lstm_LSTM_output_0_output2),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 9, &_lstm_LSTM_output_0_kernel, &_lstm_LSTM_output_0_recurrent, NULL, NULL, NULL, &_lstm_LSTM_output_0_bias, &_lstm_LSTM_output_0_initial_h, &_lstm_LSTM_output_0_initial_c, &_lstm_LSTM_output_0_peepholes),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &_lstm_LSTM_output_0_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  _lstm_LSTM_output_0_layer, 22,
  LSTM_TYPE, 0x0, NULL,
  lstm, forward_lstm,
  &_lstm_LSTM_output_0_chain,
  NULL, &_lstm_LSTM_1_output_0_layer, AI_STATIC, 
  .n_units = 64, 
  .activation_nl = nl_func_tanh_array_f32, 
  .go_backwards = false, 
  .reverse_seq = false, 
  .return_state = true, 
  .out_nl = nl_func_tanh_array_f32, 
  .recurrent_nl = nl_func_sigmoid_array_f32, 
  .cell_clip = 3e+38, 
  .state = AI_HANDLE_PTR(NULL), 
  .init = AI_LAYER_FUNC(NULL), 
  .destroy = AI_LAYER_FUNC(NULL), 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 202004, 1, 1),
    202004, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 17664, 1, 1),
    17664, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_1_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_1_OUT_NUM, &output_output),
  &_lstm_LSTM_output_0_layer, 0x59b1da38, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 202004, 1, 1),
      202004, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 17664, 1, 1),
      17664, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_1_IN_NUM, &input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_1_OUT_NUM, &output_output),
  &_lstm_LSTM_output_0_layer, 0x59b1da38, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_1_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_1_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    input_output_array.data = AI_PTR(g_network_1_activations_map[0] + 136);
    input_output_array.data_start = AI_PTR(g_network_1_activations_map[0] + 136);
    _lstm_LSTM_output_0_scratch0_array.data = AI_PTR(g_network_1_activations_map[0] + 256);
    _lstm_LSTM_output_0_scratch0_array.data_start = AI_PTR(g_network_1_activations_map[0] + 256);
    _lstm_LSTM_output_0_output0_array.data = AI_PTR(g_network_1_activations_map[0] + 2048);
    _lstm_LSTM_output_0_output0_array.data_start = AI_PTR(g_network_1_activations_map[0] + 2048);
    _lstm_LSTM_output_0_output1_array.data = AI_PTR(g_network_1_activations_map[0] + 9728);
    _lstm_LSTM_output_0_output1_array.data_start = AI_PTR(g_network_1_activations_map[0] + 9728);
    _lstm_LSTM_output_0_output2_array.data = AI_PTR(g_network_1_activations_map[0] + 9984);
    _lstm_LSTM_output_0_output2_array.data_start = AI_PTR(g_network_1_activations_map[0] + 9984);
    _lstm_LSTM_1_output_0_scratch0_array.data = AI_PTR(g_network_1_activations_map[0] + 256);
    _lstm_LSTM_1_output_0_scratch0_array.data_start = AI_PTR(g_network_1_activations_map[0] + 256);
    _lstm_LSTM_1_output_0_output0_array.data = AI_PTR(g_network_1_activations_map[0] + 9728);
    _lstm_LSTM_1_output_0_output0_array.data_start = AI_PTR(g_network_1_activations_map[0] + 9728);
    _lstm_LSTM_1_output_0_output1_array.data = AI_PTR(g_network_1_activations_map[0] + 0);
    _lstm_LSTM_1_output_0_output1_array.data_start = AI_PTR(g_network_1_activations_map[0] + 0);
    _lstm_LSTM_1_output_0_output2_array.data = AI_PTR(g_network_1_activations_map[0] + 17408);
    _lstm_LSTM_1_output_0_output2_array.data_start = AI_PTR(g_network_1_activations_map[0] + 17408);
    _Gather_output_0_output_array.data = AI_PTR(g_network_1_activations_map[0] + 0);
    _Gather_output_0_output_array.data_start = AI_PTR(g_network_1_activations_map[0] + 0);
    output_output_array.data = AI_PTR(g_network_1_activations_map[0] + 256);
    output_output_array.data_start = AI_PTR(g_network_1_activations_map[0] + 256);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_1_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network_1_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    _lstm_LSTM_output_0_kernel_array.format |= AI_FMT_FLAG_CONST;
    _lstm_LSTM_output_0_kernel_array.data = AI_PTR(g_network_1_weights_map[0] + 0);
    _lstm_LSTM_output_0_kernel_array.data_start = AI_PTR(g_network_1_weights_map[0] + 0);
    _lstm_LSTM_output_0_recurrent_array.format |= AI_FMT_FLAG_CONST;
    _lstm_LSTM_output_0_recurrent_array.data = AI_PTR(g_network_1_weights_map[0] + 1024);
    _lstm_LSTM_output_0_recurrent_array.data_start = AI_PTR(g_network_1_weights_map[0] + 1024);
    _lstm_LSTM_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _lstm_LSTM_output_0_bias_array.data = AI_PTR(g_network_1_weights_map[0] + 66560);
    _lstm_LSTM_output_0_bias_array.data_start = AI_PTR(g_network_1_weights_map[0] + 66560);
    _lstm_LSTM_output_0_initial_h_array.format |= AI_FMT_FLAG_CONST;
    _lstm_LSTM_output_0_initial_h_array.data = AI_PTR(g_network_1_weights_map[0] + 67584);
    _lstm_LSTM_output_0_initial_h_array.data_start = AI_PTR(g_network_1_weights_map[0] + 67584);
    _lstm_LSTM_output_0_initial_c_array.format |= AI_FMT_FLAG_CONST;
    _lstm_LSTM_output_0_initial_c_array.data = AI_PTR(g_network_1_weights_map[0] + 67840);
    _lstm_LSTM_output_0_initial_c_array.data_start = AI_PTR(g_network_1_weights_map[0] + 67840);
    _lstm_LSTM_output_0_peepholes_array.format |= AI_FMT_FLAG_CONST;
    _lstm_LSTM_output_0_peepholes_array.data = AI_PTR(g_network_1_weights_map[0] + 68096);
    _lstm_LSTM_output_0_peepholes_array.data_start = AI_PTR(g_network_1_weights_map[0] + 68096);
    _lstm_LSTM_1_output_0_kernel_array.format |= AI_FMT_FLAG_CONST;
    _lstm_LSTM_1_output_0_kernel_array.data = AI_PTR(g_network_1_weights_map[0] + 68864);
    _lstm_LSTM_1_output_0_kernel_array.data_start = AI_PTR(g_network_1_weights_map[0] + 68864);
    _lstm_LSTM_1_output_0_recurrent_array.format |= AI_FMT_FLAG_CONST;
    _lstm_LSTM_1_output_0_recurrent_array.data = AI_PTR(g_network_1_weights_map[0] + 134400);
    _lstm_LSTM_1_output_0_recurrent_array.data_start = AI_PTR(g_network_1_weights_map[0] + 134400);
    _lstm_LSTM_1_output_0_bias_array.format |= AI_FMT_FLAG_CONST;
    _lstm_LSTM_1_output_0_bias_array.data = AI_PTR(g_network_1_weights_map[0] + 199936);
    _lstm_LSTM_1_output_0_bias_array.data_start = AI_PTR(g_network_1_weights_map[0] + 199936);
    _Constant_output_0_array.format |= AI_FMT_FLAG_CONST;
    _Constant_output_0_array.data = AI_PTR(g_network_1_weights_map[0] + 200960);
    _Constant_output_0_array.data_start = AI_PTR(g_network_1_weights_map[0] + 200960);
    output_weights_array.format |= AI_FMT_FLAG_CONST;
    output_weights_array.data = AI_PTR(g_network_1_weights_map[0] + 200964);
    output_weights_array.data_start = AI_PTR(g_network_1_weights_map[0] + 200964);
    output_bias_array.format |= AI_FMT_FLAG_CONST;
    output_bias_array.data = AI_PTR(g_network_1_weights_map[0] + 201988);
    output_bias_array.data_start = AI_PTR(g_network_1_weights_map[0] + 201988);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_1_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_1_MODEL_NAME,
      .model_signature   = AI_NETWORK_1_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1501700,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x59b1da38,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_network_1_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_1_MODEL_NAME,
      .model_signature   = AI_NETWORK_1_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1501700,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x59b1da38,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_network_1_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_network_1_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_network_1_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_network_1_create(network, AI_NETWORK_1_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_network_1_data_params_get(&params) != true) {
    err = ai_network_1_get_error(*network);
    return err;
  }
#if defined(AI_NETWORK_1_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_NETWORK_1_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_network_1_init(*network, &params) != true) {
    err = ai_network_1_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_network_1_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_network_1_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_network_1_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_network_1_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= network_1_configure_weights(net_ctx, params);
  ok &= network_1_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_1_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_network_1_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_1_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

