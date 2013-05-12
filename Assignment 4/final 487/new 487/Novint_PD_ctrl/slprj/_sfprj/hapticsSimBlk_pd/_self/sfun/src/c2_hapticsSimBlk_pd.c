/* Include files */

#include "blascompat32.h"
#include "hapticsSimBlk_pd_sfun.h"
#include "c2_hapticsSimBlk_pd.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hapticsSimBlk_pd_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[42] = { "a1", "a2", "d3", "a4", "a5",
  "a6", "L1", "L2", "L3", "L6", "input", "T01", "T12", "T23", "T34", "T45",
  "T56", "T0", "O_0", "k0", "O_1", "k1", "T02", "O_2", "k2", "O_3", "k3", "T04",
  "O_4", "k4", "T05", "O_5", "k5", "O_6", "k6", "nargin", "nargout", "q",
  "Jacobian", "T06", "T03", "Jacob_inv" };

/* Function Declarations */
static void initialize_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance);
static void initialize_params_c2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance);
static void enable_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance);
static void disable_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance);
static void set_sim_state_c2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance);
static void sf_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance);
static void c2_chartstep_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance);
static void initSimStructsc2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_Jacob_inv, const char_T *c2_identifier,
  real_T c2_y[36]);
static void c2_b_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[36]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_T03, const char_T *c2_identifier, real_T
  c2_y[16]);
static void c2_d_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_e_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_f_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_g_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[24]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[57]);
static real_T c2_mrdivide(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A, real_T c2_B);
static void c2_eml_scalar_eg(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance);
static void c2_eml_xgemm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[16], real_T c2_C[16], real_T c2_b_C[16]);
static void c2_cross(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance, real_T
                     c2_a[3], real_T c2_b[3], real_T c2_c[3]);
static void c2_inv(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance, real_T
                   c2_x[36], real_T c2_y[36]);
static void c2_eps(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance);
static void c2_eml_matlab_zgetrf(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, real_T c2_A[36], real_T c2_b_A[36], int32_T c2_ipiv[6],
  int32_T *c2_info);
static int32_T c2_eml_ixamax(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[36], int32_T c2_ix0);
static void c2_eml_xtrsm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A[36], real_T c2_B[36], real_T c2_b_B[36]);
static real_T c2_norm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance, real_T
                      c2_x[36]);
static void c2_eml_warning(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance);
static void c2_b_eml_warning(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  char_T c2_varargin_2[14]);
static void c2_h_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_sprintf, const char_T *c2_identifier, char_T
  c2_y[14]);
static void c2_i_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  char_T c2_y[14]);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_j_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_k_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_hapticsSimBlk_pd, const
  char_T *c2_identifier);
static uint8_T c2_l_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_eml_xgemm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[16], real_T c2_C[16]);
static void c2_b_eml_matlab_zgetrf(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, real_T c2_A[36], int32_T c2_ipiv[6], int32_T *c2_info);
static void c2_b_eml_xtrsm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A[36], real_T c2_B[36]);
static void init_dsm_address_info(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_hapticsSimBlk_pd = 0U;
}

static void initialize_params_c2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance)
{
}

static void enable_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[36];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i1;
  real_T c2_b_u[36];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i2;
  real_T c2_c_u[16];
  const mxArray *c2_d_y = NULL;
  int32_T c2_i3;
  real_T c2_d_u[16];
  const mxArray *c2_e_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  real_T (*c2_T06)[16];
  real_T (*c2_T03)[16];
  real_T (*c2_Jacobian)[36];
  real_T (*c2_Jacob_inv)[36];
  c2_Jacob_inv = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
  c2_T03 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_T06 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_Jacobian = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(5), FALSE);
  for (c2_i0 = 0; c2_i0 < 36; c2_i0++) {
    c2_u[c2_i0] = (*c2_Jacob_inv)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 6, 6), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  for (c2_i1 = 0; c2_i1 < 36; c2_i1++) {
    c2_b_u[c2_i1] = (*c2_Jacobian)[c2_i1];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 6, 6),
                FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  for (c2_i2 = 0; c2_i2 < 16; c2_i2++) {
    c2_c_u[c2_i2] = (*c2_T03)[c2_i2];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 4, 4),
                FALSE);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  for (c2_i3 = 0; c2_i3 < 16; c2_i3++) {
    c2_d_u[c2_i3] = (*c2_T06)[c2_i3];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 4, 4),
                FALSE);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_hapticsSimBlk_pd;
  c2_e_u = c2_hoistedGlobal;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 4, c2_f_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[36];
  int32_T c2_i4;
  real_T c2_dv1[36];
  int32_T c2_i5;
  real_T c2_dv2[16];
  int32_T c2_i6;
  real_T c2_dv3[16];
  int32_T c2_i7;
  real_T (*c2_Jacob_inv)[36];
  real_T (*c2_Jacobian)[36];
  real_T (*c2_T03)[16];
  real_T (*c2_T06)[16];
  c2_Jacob_inv = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
  c2_T03 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_T06 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_Jacobian = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                      "Jacob_inv", c2_dv0);
  for (c2_i4 = 0; c2_i4 < 36; c2_i4++) {
    (*c2_Jacob_inv)[c2_i4] = c2_dv0[c2_i4];
  }

  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
                      "Jacobian", c2_dv1);
  for (c2_i5 = 0; c2_i5 < 36; c2_i5++) {
    (*c2_Jacobian)[c2_i5] = c2_dv1[c2_i5];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 2)),
                        "T03", c2_dv2);
  for (c2_i6 = 0; c2_i6 < 16; c2_i6++) {
    (*c2_T03)[c2_i6] = c2_dv2[c2_i6];
  }

  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 3)),
                        "T06", c2_dv3);
  for (c2_i7 = 0; c2_i7 < 16; c2_i7++) {
    (*c2_T06)[c2_i7] = c2_dv3[c2_i7];
  }

  chartInstance->c2_is_active_c2_hapticsSimBlk_pd = c2_k_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 4)),
     "is_active_c2_hapticsSimBlk_pd");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_hapticsSimBlk_pd(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance)
{
}

static void sf_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance)
{
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  real_T (*c2_Jacob_inv)[36];
  real_T (*c2_T03)[16];
  real_T (*c2_T06)[16];
  real_T (*c2_Jacobian)[36];
  real_T (*c2_q)[6];
  c2_Jacob_inv = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
  c2_T03 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_T06 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_Jacobian = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_q = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i8 = 0; c2_i8 < 6; c2_i8++) {
    _SFD_DATA_RANGE_CHECK((*c2_q)[c2_i8], 0U);
  }

  for (c2_i9 = 0; c2_i9 < 36; c2_i9++) {
    _SFD_DATA_RANGE_CHECK((*c2_Jacobian)[c2_i9], 1U);
  }

  for (c2_i10 = 0; c2_i10 < 16; c2_i10++) {
    _SFD_DATA_RANGE_CHECK((*c2_T06)[c2_i10], 2U);
  }

  for (c2_i11 = 0; c2_i11 < 16; c2_i11++) {
    _SFD_DATA_RANGE_CHECK((*c2_T03)[c2_i11], 3U);
  }

  for (c2_i12 = 0; c2_i12 < 36; c2_i12++) {
    _SFD_DATA_RANGE_CHECK((*c2_Jacob_inv)[c2_i12], 4U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_hapticsSimBlk_pd(chartInstance);
  sf_debug_check_for_state_inconsistency(_hapticsSimBlk_pdMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_hapticsSimBlk_pd(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance)
{
  int32_T c2_i13;
  real_T c2_q[6];
  uint32_T c2_debug_family_var_map[42];
  real_T c2_a1;
  real_T c2_a2;
  real_T c2_d3;
  real_T c2_a4;
  real_T c2_a5;
  real_T c2_a6;
  real_T c2_L1;
  real_T c2_L2;
  real_T c2_L3;
  real_T c2_L6;
  real_T c2_input[24];
  real_T c2_T01[16];
  real_T c2_T12[16];
  real_T c2_T23[16];
  real_T c2_T34[16];
  real_T c2_T45[16];
  real_T c2_T56[16];
  real_T c2_T0[16];
  real_T c2_O_0[3];
  real_T c2_k0[3];
  real_T c2_O_1[3];
  real_T c2_k1[3];
  real_T c2_T02[16];
  real_T c2_O_2[3];
  real_T c2_k2[3];
  real_T c2_O_3[3];
  real_T c2_k3[3];
  real_T c2_T04[16];
  real_T c2_O_4[3];
  real_T c2_k4[3];
  real_T c2_T05[16];
  real_T c2_O_5[3];
  real_T c2_k5[3];
  real_T c2_O_6[3];
  real_T c2_k6[3];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 4.0;
  real_T c2_Jacobian[36];
  real_T c2_T06[16];
  real_T c2_T03[16];
  real_T c2_Jacob_inv[36];
  real_T c2_d0;
  real_T c2_d1;
  real_T c2_d2;
  real_T c2_b_d3;
  real_T c2_d4;
  real_T c2_d5;
  real_T c2_d6;
  real_T c2_d7;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_a;
  real_T c2_b;
  real_T c2_y;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_b_y;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_c_a;
  real_T c2_c_b;
  real_T c2_c_y;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_d_a;
  real_T c2_d_b;
  real_T c2_d_y;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_v_x;
  real_T c2_e_a;
  real_T c2_e_b;
  real_T c2_e_y;
  real_T c2_w_x;
  real_T c2_x_x;
  real_T c2_f_a;
  real_T c2_f_b;
  real_T c2_f_y;
  real_T c2_y_x;
  real_T c2_ab_x;
  real_T c2_bb_x;
  real_T c2_cb_x;
  int32_T c2_i14;
  int32_T c2_i15;
  static real_T c2_dv4[4] = { 0.0, 0.0, 0.0, 1.0 };

  real_T c2_db_x;
  real_T c2_eb_x;
  real_T c2_fb_x;
  real_T c2_gb_x;
  real_T c2_hb_x;
  real_T c2_ib_x;
  real_T c2_g_a;
  real_T c2_g_b;
  real_T c2_g_y;
  real_T c2_jb_x;
  real_T c2_kb_x;
  real_T c2_lb_x;
  real_T c2_mb_x;
  real_T c2_h_a;
  real_T c2_h_b;
  real_T c2_h_y;
  real_T c2_nb_x;
  real_T c2_ob_x;
  real_T c2_i_a;
  real_T c2_i_b;
  real_T c2_i_y;
  real_T c2_pb_x;
  real_T c2_qb_x;
  real_T c2_rb_x;
  real_T c2_sb_x;
  real_T c2_tb_x;
  real_T c2_ub_x;
  real_T c2_j_a;
  real_T c2_j_b;
  real_T c2_j_y;
  real_T c2_vb_x;
  real_T c2_wb_x;
  real_T c2_xb_x;
  real_T c2_yb_x;
  real_T c2_k_a;
  real_T c2_k_b;
  real_T c2_k_y;
  real_T c2_ac_x;
  real_T c2_bc_x;
  real_T c2_l_a;
  real_T c2_l_b;
  real_T c2_l_y;
  real_T c2_cc_x;
  real_T c2_dc_x;
  real_T c2_ec_x;
  real_T c2_fc_x;
  int32_T c2_i16;
  int32_T c2_i17;
  real_T c2_gc_x;
  real_T c2_hc_x;
  real_T c2_ic_x;
  real_T c2_jc_x;
  real_T c2_kc_x;
  real_T c2_lc_x;
  real_T c2_m_a;
  real_T c2_m_b;
  real_T c2_m_y;
  real_T c2_mc_x;
  real_T c2_nc_x;
  real_T c2_oc_x;
  real_T c2_pc_x;
  real_T c2_n_a;
  real_T c2_n_b;
  real_T c2_n_y;
  real_T c2_qc_x;
  real_T c2_rc_x;
  real_T c2_o_a;
  real_T c2_o_b;
  real_T c2_o_y;
  real_T c2_sc_x;
  real_T c2_tc_x;
  real_T c2_uc_x;
  real_T c2_vc_x;
  real_T c2_wc_x;
  real_T c2_xc_x;
  real_T c2_p_a;
  real_T c2_p_b;
  real_T c2_p_y;
  real_T c2_yc_x;
  real_T c2_ad_x;
  real_T c2_bd_x;
  real_T c2_cd_x;
  real_T c2_q_a;
  real_T c2_q_b;
  real_T c2_q_y;
  real_T c2_dd_x;
  real_T c2_ed_x;
  real_T c2_r_a;
  real_T c2_r_b;
  real_T c2_r_y;
  real_T c2_fd_x;
  real_T c2_gd_x;
  real_T c2_hd_x;
  real_T c2_id_x;
  int32_T c2_i18;
  int32_T c2_i19;
  real_T c2_jd_x;
  real_T c2_kd_x;
  real_T c2_ld_x;
  real_T c2_md_x;
  real_T c2_nd_x;
  real_T c2_od_x;
  real_T c2_s_a;
  real_T c2_s_b;
  real_T c2_s_y;
  real_T c2_pd_x;
  real_T c2_qd_x;
  real_T c2_rd_x;
  real_T c2_sd_x;
  real_T c2_t_a;
  real_T c2_t_b;
  real_T c2_t_y;
  real_T c2_td_x;
  real_T c2_ud_x;
  real_T c2_u_a;
  real_T c2_u_b;
  real_T c2_u_y;
  real_T c2_vd_x;
  real_T c2_wd_x;
  real_T c2_xd_x;
  real_T c2_yd_x;
  real_T c2_ae_x;
  real_T c2_be_x;
  real_T c2_v_a;
  real_T c2_v_b;
  real_T c2_v_y;
  real_T c2_ce_x;
  real_T c2_de_x;
  real_T c2_ee_x;
  real_T c2_fe_x;
  real_T c2_w_a;
  real_T c2_w_b;
  real_T c2_w_y;
  real_T c2_ge_x;
  real_T c2_he_x;
  real_T c2_x_a;
  real_T c2_x_b;
  real_T c2_x_y;
  real_T c2_ie_x;
  real_T c2_je_x;
  real_T c2_ke_x;
  real_T c2_le_x;
  int32_T c2_i20;
  int32_T c2_i21;
  real_T c2_me_x;
  real_T c2_ne_x;
  real_T c2_oe_x;
  real_T c2_pe_x;
  real_T c2_qe_x;
  real_T c2_re_x;
  real_T c2_y_a;
  real_T c2_y_b;
  real_T c2_y_y;
  real_T c2_se_x;
  real_T c2_te_x;
  real_T c2_ue_x;
  real_T c2_ve_x;
  real_T c2_ab_a;
  real_T c2_ab_b;
  real_T c2_ab_y;
  real_T c2_we_x;
  real_T c2_xe_x;
  real_T c2_bb_a;
  real_T c2_bb_b;
  real_T c2_bb_y;
  real_T c2_ye_x;
  real_T c2_af_x;
  real_T c2_bf_x;
  real_T c2_cf_x;
  real_T c2_df_x;
  real_T c2_ef_x;
  real_T c2_cb_a;
  real_T c2_cb_b;
  real_T c2_cb_y;
  real_T c2_ff_x;
  real_T c2_gf_x;
  real_T c2_hf_x;
  real_T c2_if_x;
  real_T c2_db_a;
  real_T c2_db_b;
  real_T c2_db_y;
  real_T c2_jf_x;
  real_T c2_kf_x;
  real_T c2_eb_a;
  real_T c2_eb_b;
  real_T c2_eb_y;
  real_T c2_lf_x;
  real_T c2_mf_x;
  real_T c2_nf_x;
  real_T c2_of_x;
  int32_T c2_i22;
  int32_T c2_i23;
  real_T c2_pf_x;
  real_T c2_qf_x;
  real_T c2_rf_x;
  real_T c2_sf_x;
  real_T c2_tf_x;
  real_T c2_uf_x;
  real_T c2_fb_a;
  real_T c2_fb_b;
  real_T c2_fb_y;
  real_T c2_vf_x;
  real_T c2_wf_x;
  real_T c2_xf_x;
  real_T c2_yf_x;
  real_T c2_gb_a;
  real_T c2_gb_b;
  real_T c2_gb_y;
  real_T c2_ag_x;
  real_T c2_bg_x;
  real_T c2_hb_a;
  real_T c2_hb_b;
  real_T c2_hb_y;
  real_T c2_cg_x;
  real_T c2_dg_x;
  real_T c2_eg_x;
  real_T c2_fg_x;
  real_T c2_gg_x;
  real_T c2_hg_x;
  real_T c2_ib_a;
  real_T c2_ib_b;
  real_T c2_ib_y;
  real_T c2_ig_x;
  real_T c2_jg_x;
  real_T c2_kg_x;
  real_T c2_lg_x;
  real_T c2_jb_a;
  real_T c2_jb_b;
  real_T c2_jb_y;
  real_T c2_mg_x;
  real_T c2_ng_x;
  real_T c2_kb_a;
  real_T c2_kb_b;
  real_T c2_kb_y;
  real_T c2_og_x;
  real_T c2_pg_x;
  real_T c2_qg_x;
  real_T c2_rg_x;
  int32_T c2_i24;
  int32_T c2_i25;
  int32_T c2_i26;
  static real_T c2_lb_a[16] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c2_i27;
  int32_T c2_i28;
  static real_T c2_dv5[3] = { 0.0, 0.0, 1.0 };

  int32_T c2_i29;
  real_T c2_lb_b[16];
  int32_T c2_i30;
  int32_T c2_i31;
  int32_T c2_i32;
  real_T c2_mb_a[16];
  int32_T c2_i33;
  real_T c2_mb_b[16];
  int32_T c2_i34;
  int32_T c2_i35;
  int32_T c2_i36;
  real_T c2_nb_a[16];
  int32_T c2_i37;
  int32_T c2_i38;
  int32_T c2_i39;
  int32_T c2_i40;
  real_T c2_ob_a[16];
  int32_T c2_i41;
  real_T c2_nb_b[16];
  int32_T c2_i42;
  int32_T c2_i43;
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_i46;
  int32_T c2_i47;
  int32_T c2_i48;
  real_T c2_pb_a[16];
  int32_T c2_i49;
  real_T c2_ob_b[16];
  int32_T c2_i50;
  int32_T c2_i51;
  int32_T c2_i52;
  int32_T c2_i53;
  int32_T c2_i54;
  int32_T c2_i55;
  int32_T c2_i56;
  real_T c2_qb_a[16];
  int32_T c2_i57;
  real_T c2_pb_b[16];
  int32_T c2_i58;
  int32_T c2_i59;
  int32_T c2_i60;
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_i63;
  int32_T c2_i64;
  real_T c2_rb_a[16];
  int32_T c2_i65;
  real_T c2_qb_b[16];
  int32_T c2_i66;
  int32_T c2_i67;
  int32_T c2_i68;
  int32_T c2_i69;
  int32_T c2_i70;
  int32_T c2_i71;
  int32_T c2_i72;
  real_T c2_sb_a[16];
  int32_T c2_i73;
  real_T c2_rb_b[16];
  int32_T c2_i74;
  int32_T c2_i75;
  int32_T c2_i76;
  real_T c2_dv6[3];
  int32_T c2_i77;
  real_T c2_b_O_6[3];
  real_T c2_dv7[3];
  int32_T c2_i78;
  real_T c2_b_k1[3];
  int32_T c2_i79;
  real_T c2_c_O_6[3];
  real_T c2_dv8[3];
  int32_T c2_i80;
  real_T c2_b_k3[3];
  int32_T c2_i81;
  real_T c2_d_O_6[3];
  real_T c2_dv9[3];
  int32_T c2_i82;
  real_T c2_b_k4[3];
  int32_T c2_i83;
  real_T c2_e_O_6[3];
  real_T c2_dv10[3];
  int32_T c2_i84;
  real_T c2_b_k5[3];
  int32_T c2_i85;
  real_T c2_f_O_6[3];
  real_T c2_dv11[3];
  int32_T c2_i86;
  real_T c2_dv12[3];
  int32_T c2_i87;
  int32_T c2_i88;
  int32_T c2_i89;
  int32_T c2_i90;
  int32_T c2_i91;
  int32_T c2_i92;
  int32_T c2_i93;
  int32_T c2_i94;
  int32_T c2_i95;
  int32_T c2_i96;
  int32_T c2_i97;
  int32_T c2_i98;
  int32_T c2_i99;
  real_T c2_b_Jacobian[36];
  real_T c2_dv13[36];
  int32_T c2_i100;
  int32_T c2_i101;
  real_T c2_u[36];
  const mxArray *c2_lb_y = NULL;
  int32_T c2_i102;
  int32_T c2_i103;
  int32_T c2_i104;
  int32_T c2_i105;
  real_T (*c2_c_Jacobian)[36];
  real_T (*c2_b_T06)[16];
  real_T (*c2_b_T03)[16];
  real_T (*c2_b_Jacob_inv)[36];
  real_T (*c2_b_q)[6];
  c2_b_Jacob_inv = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 4);
  c2_b_T03 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 3);
  c2_b_T06 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 2);
  c2_c_Jacobian = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_q = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  for (c2_i13 = 0; c2_i13 < 6; c2_i13++) {
    c2_q[c2_i13] = (*c2_b_q)[c2_i13];
  }

  sf_debug_symbol_scope_push_eml(0U, 42U, 42U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_a1, 0U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_a2, 1U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_d3, 2U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_a4, 3U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_a5, 4U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_a6, 5U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_L1, 6U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_L2, 7U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_L3, 8U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_L6, 9U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_input, 10U, c2_f_sf_marshallOut,
    c2_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T01, 11U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T12, 12U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T23, 13U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T34, 14U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T45, 15U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T56, 16U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_T0, 17U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_O_0, 18U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_k0, 19U, c2_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_O_1, 20U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_k1, 21U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T02, 22U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_O_2, 23U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_k2, 24U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_O_3, 25U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_k3, 26U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T04, 27U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_O_4, 28U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_k4, 29U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T05, 30U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_O_5, 31U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_k5, 32U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_O_6, 33U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_k6, 34U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 35U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 36U, c2_d_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_q, 37U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_Jacobian, 38U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T06, 39U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_T03, 40U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Jacob_inv, 41U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  c2_a1 = c2_q[0];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_a2 = c2_q[1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  c2_d3 = c2_q[2];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_a4 = c2_q[3];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  c2_a5 = c2_q[4];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_a6 = c2_q[5];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  c2_L1 = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  c2_L2 = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  c2_L3 = 0.5;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  c2_L6 = 0.2;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  c2_d0 = c2_mrdivide(chartInstance, 3.1415926535897931, 2.0);
  c2_d1 = c2_mrdivide(chartInstance, -3.1415926535897931, 2.0);
  c2_d2 = c2_mrdivide(chartInstance, -3.1415926535897931, 2.0);
  c2_b_d3 = c2_mrdivide(chartInstance, -3.1415926535897931, 2.0);
  c2_d4 = c2_mrdivide(chartInstance, -3.1415926535897931, 2.0);
  c2_d5 = c2_mrdivide(chartInstance, -3.1415926535897931, 2.0);
  c2_d6 = c2_mrdivide(chartInstance, 3.1415926535897931, 2.0);
  c2_d7 = c2_mrdivide(chartInstance, -3.1415926535897931, 2.0);
  c2_input[0] = c2_d0 + c2_a1;
  c2_input[6] = c2_L6 + c2_L3;
  c2_input[12] = c2_L1;
  c2_input[18] = 0.0;
  c2_input[1] = c2_a2;
  c2_input[7] = 0.0;
  c2_input[13] = c2_L2;
  c2_input[19] = 0.0;
  c2_input[2] = c2_d1;
  c2_input[8] = -c2_L3 + c2_d3;
  c2_input[14] = 0.0;
  c2_input[20] = c2_d2;
  c2_input[3] = c2_b_d3 + c2_a4;
  c2_input[9] = 0.0;
  c2_input[15] = 0.0;
  c2_input[21] = c2_d4;
  c2_input[4] = c2_d5 + c2_a5;
  c2_input[10] = 0.0;
  c2_input[16] = 0.0;
  c2_input[22] = c2_d6;
  c2_input[5] = c2_d7 + c2_a6;
  c2_input[11] = -c2_L6;
  c2_input[17] = 0.0;
  c2_input[23] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 23);
  c2_x = c2_input[0];
  c2_b_x = c2_x;
  c2_b_x = muDoubleScalarCos(c2_b_x);
  c2_c_x = c2_input[0];
  c2_d_x = c2_c_x;
  c2_d_x = muDoubleScalarSin(c2_d_x);
  c2_e_x = c2_input[18];
  c2_f_x = c2_e_x;
  c2_f_x = muDoubleScalarCos(c2_f_x);
  c2_a = -c2_d_x;
  c2_b = c2_f_x;
  c2_y = c2_a * c2_b;
  c2_g_x = c2_input[0];
  c2_h_x = c2_g_x;
  c2_h_x = muDoubleScalarSin(c2_h_x);
  c2_i_x = c2_input[18];
  c2_j_x = c2_i_x;
  c2_j_x = muDoubleScalarSin(c2_j_x);
  c2_b_a = c2_h_x;
  c2_b_b = c2_j_x;
  c2_b_y = c2_b_a * c2_b_b;
  c2_k_x = c2_input[0];
  c2_l_x = c2_k_x;
  c2_l_x = muDoubleScalarCos(c2_l_x);
  c2_c_a = c2_input[12];
  c2_c_b = c2_l_x;
  c2_c_y = c2_c_a * c2_c_b;
  c2_m_x = c2_input[0];
  c2_n_x = c2_m_x;
  c2_n_x = muDoubleScalarSin(c2_n_x);
  c2_o_x = c2_input[0];
  c2_p_x = c2_o_x;
  c2_p_x = muDoubleScalarCos(c2_p_x);
  c2_q_x = c2_input[18];
  c2_r_x = c2_q_x;
  c2_r_x = muDoubleScalarCos(c2_r_x);
  c2_d_a = c2_p_x;
  c2_d_b = c2_r_x;
  c2_d_y = c2_d_a * c2_d_b;
  c2_s_x = c2_input[0];
  c2_t_x = c2_s_x;
  c2_t_x = muDoubleScalarCos(c2_t_x);
  c2_u_x = c2_input[18];
  c2_v_x = c2_u_x;
  c2_v_x = muDoubleScalarSin(c2_v_x);
  c2_e_a = -c2_t_x;
  c2_e_b = c2_v_x;
  c2_e_y = c2_e_a * c2_e_b;
  c2_w_x = c2_input[0];
  c2_x_x = c2_w_x;
  c2_x_x = muDoubleScalarSin(c2_x_x);
  c2_f_a = c2_input[12];
  c2_f_b = c2_x_x;
  c2_f_y = c2_f_a * c2_f_b;
  c2_y_x = c2_input[18];
  c2_ab_x = c2_y_x;
  c2_ab_x = muDoubleScalarSin(c2_ab_x);
  c2_bb_x = c2_input[18];
  c2_cb_x = c2_bb_x;
  c2_cb_x = muDoubleScalarCos(c2_cb_x);
  c2_T01[0] = c2_b_x;
  c2_T01[4] = c2_y;
  c2_T01[8] = c2_b_y;
  c2_T01[12] = c2_c_y;
  c2_T01[1] = c2_n_x;
  c2_T01[5] = c2_d_y;
  c2_T01[9] = c2_e_y;
  c2_T01[13] = c2_f_y;
  c2_T01[2] = 0.0;
  c2_T01[6] = c2_ab_x;
  c2_T01[10] = c2_cb_x;
  c2_T01[14] = c2_input[6];
  c2_i14 = 0;
  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    c2_T01[c2_i14 + 3] = c2_dv4[c2_i15];
    c2_i14 += 4;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 27);
  c2_db_x = c2_input[1];
  c2_eb_x = c2_db_x;
  c2_eb_x = muDoubleScalarCos(c2_eb_x);
  c2_fb_x = c2_input[1];
  c2_gb_x = c2_fb_x;
  c2_gb_x = muDoubleScalarSin(c2_gb_x);
  c2_hb_x = c2_input[19];
  c2_ib_x = c2_hb_x;
  c2_ib_x = muDoubleScalarCos(c2_ib_x);
  c2_g_a = -c2_gb_x;
  c2_g_b = c2_ib_x;
  c2_g_y = c2_g_a * c2_g_b;
  c2_jb_x = c2_input[1];
  c2_kb_x = c2_jb_x;
  c2_kb_x = muDoubleScalarSin(c2_kb_x);
  c2_lb_x = c2_input[19];
  c2_mb_x = c2_lb_x;
  c2_mb_x = muDoubleScalarSin(c2_mb_x);
  c2_h_a = c2_kb_x;
  c2_h_b = c2_mb_x;
  c2_h_y = c2_h_a * c2_h_b;
  c2_nb_x = c2_input[1];
  c2_ob_x = c2_nb_x;
  c2_ob_x = muDoubleScalarCos(c2_ob_x);
  c2_i_a = c2_input[13];
  c2_i_b = c2_ob_x;
  c2_i_y = c2_i_a * c2_i_b;
  c2_pb_x = c2_input[1];
  c2_qb_x = c2_pb_x;
  c2_qb_x = muDoubleScalarSin(c2_qb_x);
  c2_rb_x = c2_input[1];
  c2_sb_x = c2_rb_x;
  c2_sb_x = muDoubleScalarCos(c2_sb_x);
  c2_tb_x = c2_input[19];
  c2_ub_x = c2_tb_x;
  c2_ub_x = muDoubleScalarCos(c2_ub_x);
  c2_j_a = c2_sb_x;
  c2_j_b = c2_ub_x;
  c2_j_y = c2_j_a * c2_j_b;
  c2_vb_x = c2_input[1];
  c2_wb_x = c2_vb_x;
  c2_wb_x = muDoubleScalarCos(c2_wb_x);
  c2_xb_x = c2_input[19];
  c2_yb_x = c2_xb_x;
  c2_yb_x = muDoubleScalarSin(c2_yb_x);
  c2_k_a = -c2_wb_x;
  c2_k_b = c2_yb_x;
  c2_k_y = c2_k_a * c2_k_b;
  c2_ac_x = c2_input[1];
  c2_bc_x = c2_ac_x;
  c2_bc_x = muDoubleScalarSin(c2_bc_x);
  c2_l_a = c2_input[13];
  c2_l_b = c2_bc_x;
  c2_l_y = c2_l_a * c2_l_b;
  c2_cc_x = c2_input[19];
  c2_dc_x = c2_cc_x;
  c2_dc_x = muDoubleScalarSin(c2_dc_x);
  c2_ec_x = c2_input[19];
  c2_fc_x = c2_ec_x;
  c2_fc_x = muDoubleScalarCos(c2_fc_x);
  c2_T12[0] = c2_eb_x;
  c2_T12[4] = c2_g_y;
  c2_T12[8] = c2_h_y;
  c2_T12[12] = c2_i_y;
  c2_T12[1] = c2_qb_x;
  c2_T12[5] = c2_j_y;
  c2_T12[9] = c2_k_y;
  c2_T12[13] = c2_l_y;
  c2_T12[2] = 0.0;
  c2_T12[6] = c2_dc_x;
  c2_T12[10] = c2_fc_x;
  c2_T12[14] = c2_input[7];
  c2_i16 = 0;
  for (c2_i17 = 0; c2_i17 < 4; c2_i17++) {
    c2_T12[c2_i16 + 3] = c2_dv4[c2_i17];
    c2_i16 += 4;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_gc_x = c2_input[2];
  c2_hc_x = c2_gc_x;
  c2_hc_x = muDoubleScalarCos(c2_hc_x);
  c2_ic_x = c2_input[2];
  c2_jc_x = c2_ic_x;
  c2_jc_x = muDoubleScalarSin(c2_jc_x);
  c2_kc_x = c2_input[20];
  c2_lc_x = c2_kc_x;
  c2_lc_x = muDoubleScalarCos(c2_lc_x);
  c2_m_a = -c2_jc_x;
  c2_m_b = c2_lc_x;
  c2_m_y = c2_m_a * c2_m_b;
  c2_mc_x = c2_input[2];
  c2_nc_x = c2_mc_x;
  c2_nc_x = muDoubleScalarSin(c2_nc_x);
  c2_oc_x = c2_input[20];
  c2_pc_x = c2_oc_x;
  c2_pc_x = muDoubleScalarSin(c2_pc_x);
  c2_n_a = c2_nc_x;
  c2_n_b = c2_pc_x;
  c2_n_y = c2_n_a * c2_n_b;
  c2_qc_x = c2_input[2];
  c2_rc_x = c2_qc_x;
  c2_rc_x = muDoubleScalarCos(c2_rc_x);
  c2_o_a = c2_input[14];
  c2_o_b = c2_rc_x;
  c2_o_y = c2_o_a * c2_o_b;
  c2_sc_x = c2_input[2];
  c2_tc_x = c2_sc_x;
  c2_tc_x = muDoubleScalarSin(c2_tc_x);
  c2_uc_x = c2_input[2];
  c2_vc_x = c2_uc_x;
  c2_vc_x = muDoubleScalarCos(c2_vc_x);
  c2_wc_x = c2_input[20];
  c2_xc_x = c2_wc_x;
  c2_xc_x = muDoubleScalarCos(c2_xc_x);
  c2_p_a = c2_vc_x;
  c2_p_b = c2_xc_x;
  c2_p_y = c2_p_a * c2_p_b;
  c2_yc_x = c2_input[2];
  c2_ad_x = c2_yc_x;
  c2_ad_x = muDoubleScalarCos(c2_ad_x);
  c2_bd_x = c2_input[20];
  c2_cd_x = c2_bd_x;
  c2_cd_x = muDoubleScalarSin(c2_cd_x);
  c2_q_a = -c2_ad_x;
  c2_q_b = c2_cd_x;
  c2_q_y = c2_q_a * c2_q_b;
  c2_dd_x = c2_input[2];
  c2_ed_x = c2_dd_x;
  c2_ed_x = muDoubleScalarSin(c2_ed_x);
  c2_r_a = c2_input[14];
  c2_r_b = c2_ed_x;
  c2_r_y = c2_r_a * c2_r_b;
  c2_fd_x = c2_input[20];
  c2_gd_x = c2_fd_x;
  c2_gd_x = muDoubleScalarSin(c2_gd_x);
  c2_hd_x = c2_input[20];
  c2_id_x = c2_hd_x;
  c2_id_x = muDoubleScalarCos(c2_id_x);
  c2_T23[0] = c2_hc_x;
  c2_T23[4] = c2_m_y;
  c2_T23[8] = c2_n_y;
  c2_T23[12] = c2_o_y;
  c2_T23[1] = c2_tc_x;
  c2_T23[5] = c2_p_y;
  c2_T23[9] = c2_q_y;
  c2_T23[13] = c2_r_y;
  c2_T23[2] = 0.0;
  c2_T23[6] = c2_gd_x;
  c2_T23[10] = c2_id_x;
  c2_T23[14] = c2_input[8];
  c2_i18 = 0;
  for (c2_i19 = 0; c2_i19 < 4; c2_i19++) {
    c2_T23[c2_i18 + 3] = c2_dv4[c2_i19];
    c2_i18 += 4;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
  c2_jd_x = c2_input[3];
  c2_kd_x = c2_jd_x;
  c2_kd_x = muDoubleScalarCos(c2_kd_x);
  c2_ld_x = c2_input[3];
  c2_md_x = c2_ld_x;
  c2_md_x = muDoubleScalarSin(c2_md_x);
  c2_nd_x = c2_input[21];
  c2_od_x = c2_nd_x;
  c2_od_x = muDoubleScalarCos(c2_od_x);
  c2_s_a = -c2_md_x;
  c2_s_b = c2_od_x;
  c2_s_y = c2_s_a * c2_s_b;
  c2_pd_x = c2_input[3];
  c2_qd_x = c2_pd_x;
  c2_qd_x = muDoubleScalarSin(c2_qd_x);
  c2_rd_x = c2_input[21];
  c2_sd_x = c2_rd_x;
  c2_sd_x = muDoubleScalarSin(c2_sd_x);
  c2_t_a = c2_qd_x;
  c2_t_b = c2_sd_x;
  c2_t_y = c2_t_a * c2_t_b;
  c2_td_x = c2_input[3];
  c2_ud_x = c2_td_x;
  c2_ud_x = muDoubleScalarCos(c2_ud_x);
  c2_u_a = c2_input[15];
  c2_u_b = c2_ud_x;
  c2_u_y = c2_u_a * c2_u_b;
  c2_vd_x = c2_input[3];
  c2_wd_x = c2_vd_x;
  c2_wd_x = muDoubleScalarSin(c2_wd_x);
  c2_xd_x = c2_input[3];
  c2_yd_x = c2_xd_x;
  c2_yd_x = muDoubleScalarCos(c2_yd_x);
  c2_ae_x = c2_input[21];
  c2_be_x = c2_ae_x;
  c2_be_x = muDoubleScalarCos(c2_be_x);
  c2_v_a = c2_yd_x;
  c2_v_b = c2_be_x;
  c2_v_y = c2_v_a * c2_v_b;
  c2_ce_x = c2_input[3];
  c2_de_x = c2_ce_x;
  c2_de_x = muDoubleScalarCos(c2_de_x);
  c2_ee_x = c2_input[21];
  c2_fe_x = c2_ee_x;
  c2_fe_x = muDoubleScalarSin(c2_fe_x);
  c2_w_a = -c2_de_x;
  c2_w_b = c2_fe_x;
  c2_w_y = c2_w_a * c2_w_b;
  c2_ge_x = c2_input[3];
  c2_he_x = c2_ge_x;
  c2_he_x = muDoubleScalarSin(c2_he_x);
  c2_x_a = c2_input[15];
  c2_x_b = c2_he_x;
  c2_x_y = c2_x_a * c2_x_b;
  c2_ie_x = c2_input[21];
  c2_je_x = c2_ie_x;
  c2_je_x = muDoubleScalarSin(c2_je_x);
  c2_ke_x = c2_input[21];
  c2_le_x = c2_ke_x;
  c2_le_x = muDoubleScalarCos(c2_le_x);
  c2_T34[0] = c2_kd_x;
  c2_T34[4] = c2_s_y;
  c2_T34[8] = c2_t_y;
  c2_T34[12] = c2_u_y;
  c2_T34[1] = c2_wd_x;
  c2_T34[5] = c2_v_y;
  c2_T34[9] = c2_w_y;
  c2_T34[13] = c2_x_y;
  c2_T34[2] = 0.0;
  c2_T34[6] = c2_je_x;
  c2_T34[10] = c2_le_x;
  c2_T34[14] = c2_input[9];
  c2_i20 = 0;
  for (c2_i21 = 0; c2_i21 < 4; c2_i21++) {
    c2_T34[c2_i20 + 3] = c2_dv4[c2_i21];
    c2_i20 += 4;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
  c2_me_x = c2_input[4];
  c2_ne_x = c2_me_x;
  c2_ne_x = muDoubleScalarCos(c2_ne_x);
  c2_oe_x = c2_input[4];
  c2_pe_x = c2_oe_x;
  c2_pe_x = muDoubleScalarSin(c2_pe_x);
  c2_qe_x = c2_input[22];
  c2_re_x = c2_qe_x;
  c2_re_x = muDoubleScalarCos(c2_re_x);
  c2_y_a = -c2_pe_x;
  c2_y_b = c2_re_x;
  c2_y_y = c2_y_a * c2_y_b;
  c2_se_x = c2_input[4];
  c2_te_x = c2_se_x;
  c2_te_x = muDoubleScalarSin(c2_te_x);
  c2_ue_x = c2_input[22];
  c2_ve_x = c2_ue_x;
  c2_ve_x = muDoubleScalarSin(c2_ve_x);
  c2_ab_a = c2_te_x;
  c2_ab_b = c2_ve_x;
  c2_ab_y = c2_ab_a * c2_ab_b;
  c2_we_x = c2_input[4];
  c2_xe_x = c2_we_x;
  c2_xe_x = muDoubleScalarCos(c2_xe_x);
  c2_bb_a = c2_input[16];
  c2_bb_b = c2_xe_x;
  c2_bb_y = c2_bb_a * c2_bb_b;
  c2_ye_x = c2_input[4];
  c2_af_x = c2_ye_x;
  c2_af_x = muDoubleScalarSin(c2_af_x);
  c2_bf_x = c2_input[4];
  c2_cf_x = c2_bf_x;
  c2_cf_x = muDoubleScalarCos(c2_cf_x);
  c2_df_x = c2_input[22];
  c2_ef_x = c2_df_x;
  c2_ef_x = muDoubleScalarCos(c2_ef_x);
  c2_cb_a = c2_cf_x;
  c2_cb_b = c2_ef_x;
  c2_cb_y = c2_cb_a * c2_cb_b;
  c2_ff_x = c2_input[4];
  c2_gf_x = c2_ff_x;
  c2_gf_x = muDoubleScalarCos(c2_gf_x);
  c2_hf_x = c2_input[22];
  c2_if_x = c2_hf_x;
  c2_if_x = muDoubleScalarSin(c2_if_x);
  c2_db_a = -c2_gf_x;
  c2_db_b = c2_if_x;
  c2_db_y = c2_db_a * c2_db_b;
  c2_jf_x = c2_input[4];
  c2_kf_x = c2_jf_x;
  c2_kf_x = muDoubleScalarSin(c2_kf_x);
  c2_eb_a = c2_input[16];
  c2_eb_b = c2_kf_x;
  c2_eb_y = c2_eb_a * c2_eb_b;
  c2_lf_x = c2_input[22];
  c2_mf_x = c2_lf_x;
  c2_mf_x = muDoubleScalarSin(c2_mf_x);
  c2_nf_x = c2_input[22];
  c2_of_x = c2_nf_x;
  c2_of_x = muDoubleScalarCos(c2_of_x);
  c2_T45[0] = c2_ne_x;
  c2_T45[4] = c2_y_y;
  c2_T45[8] = c2_ab_y;
  c2_T45[12] = c2_bb_y;
  c2_T45[1] = c2_af_x;
  c2_T45[5] = c2_cb_y;
  c2_T45[9] = c2_db_y;
  c2_T45[13] = c2_eb_y;
  c2_T45[2] = 0.0;
  c2_T45[6] = c2_mf_x;
  c2_T45[10] = c2_of_x;
  c2_T45[14] = c2_input[10];
  c2_i22 = 0;
  for (c2_i23 = 0; c2_i23 < 4; c2_i23++) {
    c2_T45[c2_i22 + 3] = c2_dv4[c2_i23];
    c2_i22 += 4;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  c2_pf_x = c2_input[5];
  c2_qf_x = c2_pf_x;
  c2_qf_x = muDoubleScalarCos(c2_qf_x);
  c2_rf_x = c2_input[5];
  c2_sf_x = c2_rf_x;
  c2_sf_x = muDoubleScalarSin(c2_sf_x);
  c2_tf_x = c2_input[23];
  c2_uf_x = c2_tf_x;
  c2_uf_x = muDoubleScalarCos(c2_uf_x);
  c2_fb_a = -c2_sf_x;
  c2_fb_b = c2_uf_x;
  c2_fb_y = c2_fb_a * c2_fb_b;
  c2_vf_x = c2_input[5];
  c2_wf_x = c2_vf_x;
  c2_wf_x = muDoubleScalarSin(c2_wf_x);
  c2_xf_x = c2_input[23];
  c2_yf_x = c2_xf_x;
  c2_yf_x = muDoubleScalarSin(c2_yf_x);
  c2_gb_a = c2_wf_x;
  c2_gb_b = c2_yf_x;
  c2_gb_y = c2_gb_a * c2_gb_b;
  c2_ag_x = c2_input[5];
  c2_bg_x = c2_ag_x;
  c2_bg_x = muDoubleScalarCos(c2_bg_x);
  c2_hb_a = c2_input[17];
  c2_hb_b = c2_bg_x;
  c2_hb_y = c2_hb_a * c2_hb_b;
  c2_cg_x = c2_input[5];
  c2_dg_x = c2_cg_x;
  c2_dg_x = muDoubleScalarSin(c2_dg_x);
  c2_eg_x = c2_input[5];
  c2_fg_x = c2_eg_x;
  c2_fg_x = muDoubleScalarCos(c2_fg_x);
  c2_gg_x = c2_input[23];
  c2_hg_x = c2_gg_x;
  c2_hg_x = muDoubleScalarCos(c2_hg_x);
  c2_ib_a = c2_fg_x;
  c2_ib_b = c2_hg_x;
  c2_ib_y = c2_ib_a * c2_ib_b;
  c2_ig_x = c2_input[5];
  c2_jg_x = c2_ig_x;
  c2_jg_x = muDoubleScalarCos(c2_jg_x);
  c2_kg_x = c2_input[23];
  c2_lg_x = c2_kg_x;
  c2_lg_x = muDoubleScalarSin(c2_lg_x);
  c2_jb_a = -c2_jg_x;
  c2_jb_b = c2_lg_x;
  c2_jb_y = c2_jb_a * c2_jb_b;
  c2_mg_x = c2_input[5];
  c2_ng_x = c2_mg_x;
  c2_ng_x = muDoubleScalarSin(c2_ng_x);
  c2_kb_a = c2_input[17];
  c2_kb_b = c2_ng_x;
  c2_kb_y = c2_kb_a * c2_kb_b;
  c2_og_x = c2_input[23];
  c2_pg_x = c2_og_x;
  c2_pg_x = muDoubleScalarSin(c2_pg_x);
  c2_qg_x = c2_input[23];
  c2_rg_x = c2_qg_x;
  c2_rg_x = muDoubleScalarCos(c2_rg_x);
  c2_T56[0] = c2_qf_x;
  c2_T56[4] = c2_fb_y;
  c2_T56[8] = c2_gb_y;
  c2_T56[12] = c2_hb_y;
  c2_T56[1] = c2_dg_x;
  c2_T56[5] = c2_ib_y;
  c2_T56[9] = c2_jb_y;
  c2_T56[13] = c2_kb_y;
  c2_T56[2] = 0.0;
  c2_T56[6] = c2_pg_x;
  c2_T56[10] = c2_rg_x;
  c2_T56[14] = c2_input[11];
  c2_i24 = 0;
  for (c2_i25 = 0; c2_i25 < 4; c2_i25++) {
    c2_T56[c2_i24 + 3] = c2_dv4[c2_i25];
    c2_i24 += 4;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 48);
  for (c2_i26 = 0; c2_i26 < 16; c2_i26++) {
    c2_T0[c2_i26] = c2_lb_a[c2_i26];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 48);
  for (c2_i27 = 0; c2_i27 < 3; c2_i27++) {
    c2_O_0[c2_i27] = c2_T0[c2_i27 + 12];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 48);
  for (c2_i28 = 0; c2_i28 < 3; c2_i28++) {
    c2_k0[c2_i28] = c2_dv5[c2_i28];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
  for (c2_i29 = 0; c2_i29 < 16; c2_i29++) {
    c2_lb_b[c2_i29] = c2_T01[c2_i29];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  for (c2_i30 = 0; c2_i30 < 16; c2_i30++) {
    c2_T01[c2_i30] = 0.0;
  }

  for (c2_i31 = 0; c2_i31 < 16; c2_i31++) {
    c2_T01[c2_i31] = 0.0;
  }

  for (c2_i32 = 0; c2_i32 < 16; c2_i32++) {
    c2_mb_a[c2_i32] = c2_lb_a[c2_i32];
  }

  for (c2_i33 = 0; c2_i33 < 16; c2_i33++) {
    c2_mb_b[c2_i33] = c2_lb_b[c2_i33];
  }

  c2_b_eml_xgemm(chartInstance, c2_mb_a, c2_mb_b, c2_T01);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
  for (c2_i34 = 0; c2_i34 < 3; c2_i34++) {
    c2_O_1[c2_i34] = c2_T01[c2_i34 + 12];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
  for (c2_i35 = 0; c2_i35 < 3; c2_i35++) {
    c2_k1[c2_i35] = c2_T01[c2_i35 + 8];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
  for (c2_i36 = 0; c2_i36 < 16; c2_i36++) {
    c2_nb_a[c2_i36] = c2_T01[c2_i36];
  }

  for (c2_i37 = 0; c2_i37 < 16; c2_i37++) {
    c2_lb_b[c2_i37] = c2_T12[c2_i37];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  for (c2_i38 = 0; c2_i38 < 16; c2_i38++) {
    c2_T02[c2_i38] = 0.0;
  }

  for (c2_i39 = 0; c2_i39 < 16; c2_i39++) {
    c2_T02[c2_i39] = 0.0;
  }

  for (c2_i40 = 0; c2_i40 < 16; c2_i40++) {
    c2_ob_a[c2_i40] = c2_nb_a[c2_i40];
  }

  for (c2_i41 = 0; c2_i41 < 16; c2_i41++) {
    c2_nb_b[c2_i41] = c2_lb_b[c2_i41];
  }

  c2_b_eml_xgemm(chartInstance, c2_ob_a, c2_nb_b, c2_T02);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
  for (c2_i42 = 0; c2_i42 < 3; c2_i42++) {
    c2_O_2[c2_i42] = c2_T02[c2_i42 + 12];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
  for (c2_i43 = 0; c2_i43 < 3; c2_i43++) {
    c2_k2[c2_i43] = c2_T02[c2_i43 + 8];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
  for (c2_i44 = 0; c2_i44 < 16; c2_i44++) {
    c2_nb_a[c2_i44] = c2_T02[c2_i44];
  }

  for (c2_i45 = 0; c2_i45 < 16; c2_i45++) {
    c2_lb_b[c2_i45] = c2_T23[c2_i45];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  for (c2_i46 = 0; c2_i46 < 16; c2_i46++) {
    c2_T03[c2_i46] = 0.0;
  }

  for (c2_i47 = 0; c2_i47 < 16; c2_i47++) {
    c2_T03[c2_i47] = 0.0;
  }

  for (c2_i48 = 0; c2_i48 < 16; c2_i48++) {
    c2_pb_a[c2_i48] = c2_nb_a[c2_i48];
  }

  for (c2_i49 = 0; c2_i49 < 16; c2_i49++) {
    c2_ob_b[c2_i49] = c2_lb_b[c2_i49];
  }

  c2_b_eml_xgemm(chartInstance, c2_pb_a, c2_ob_b, c2_T03);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
  for (c2_i50 = 0; c2_i50 < 3; c2_i50++) {
    c2_O_3[c2_i50] = c2_T03[c2_i50 + 12];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 51);
  for (c2_i51 = 0; c2_i51 < 3; c2_i51++) {
    c2_k3[c2_i51] = c2_T03[c2_i51 + 8];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
  for (c2_i52 = 0; c2_i52 < 16; c2_i52++) {
    c2_nb_a[c2_i52] = c2_T03[c2_i52];
  }

  for (c2_i53 = 0; c2_i53 < 16; c2_i53++) {
    c2_lb_b[c2_i53] = c2_T34[c2_i53];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  for (c2_i54 = 0; c2_i54 < 16; c2_i54++) {
    c2_T04[c2_i54] = 0.0;
  }

  for (c2_i55 = 0; c2_i55 < 16; c2_i55++) {
    c2_T04[c2_i55] = 0.0;
  }

  for (c2_i56 = 0; c2_i56 < 16; c2_i56++) {
    c2_qb_a[c2_i56] = c2_nb_a[c2_i56];
  }

  for (c2_i57 = 0; c2_i57 < 16; c2_i57++) {
    c2_pb_b[c2_i57] = c2_lb_b[c2_i57];
  }

  c2_b_eml_xgemm(chartInstance, c2_qb_a, c2_pb_b, c2_T04);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
  for (c2_i58 = 0; c2_i58 < 3; c2_i58++) {
    c2_O_4[c2_i58] = c2_T04[c2_i58 + 12];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
  for (c2_i59 = 0; c2_i59 < 3; c2_i59++) {
    c2_k4[c2_i59] = c2_T04[c2_i59 + 8];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 53);
  for (c2_i60 = 0; c2_i60 < 16; c2_i60++) {
    c2_nb_a[c2_i60] = c2_T04[c2_i60];
  }

  for (c2_i61 = 0; c2_i61 < 16; c2_i61++) {
    c2_lb_b[c2_i61] = c2_T45[c2_i61];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  for (c2_i62 = 0; c2_i62 < 16; c2_i62++) {
    c2_T05[c2_i62] = 0.0;
  }

  for (c2_i63 = 0; c2_i63 < 16; c2_i63++) {
    c2_T05[c2_i63] = 0.0;
  }

  for (c2_i64 = 0; c2_i64 < 16; c2_i64++) {
    c2_rb_a[c2_i64] = c2_nb_a[c2_i64];
  }

  for (c2_i65 = 0; c2_i65 < 16; c2_i65++) {
    c2_qb_b[c2_i65] = c2_lb_b[c2_i65];
  }

  c2_b_eml_xgemm(chartInstance, c2_rb_a, c2_qb_b, c2_T05);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 53);
  for (c2_i66 = 0; c2_i66 < 3; c2_i66++) {
    c2_O_5[c2_i66] = c2_T05[c2_i66 + 12];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 53);
  for (c2_i67 = 0; c2_i67 < 3; c2_i67++) {
    c2_k5[c2_i67] = c2_T05[c2_i67 + 8];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 54);
  for (c2_i68 = 0; c2_i68 < 16; c2_i68++) {
    c2_nb_a[c2_i68] = c2_T05[c2_i68];
  }

  for (c2_i69 = 0; c2_i69 < 16; c2_i69++) {
    c2_lb_b[c2_i69] = c2_T56[c2_i69];
  }

  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  for (c2_i70 = 0; c2_i70 < 16; c2_i70++) {
    c2_T06[c2_i70] = 0.0;
  }

  for (c2_i71 = 0; c2_i71 < 16; c2_i71++) {
    c2_T06[c2_i71] = 0.0;
  }

  for (c2_i72 = 0; c2_i72 < 16; c2_i72++) {
    c2_sb_a[c2_i72] = c2_nb_a[c2_i72];
  }

  for (c2_i73 = 0; c2_i73 < 16; c2_i73++) {
    c2_rb_b[c2_i73] = c2_lb_b[c2_i73];
  }

  c2_b_eml_xgemm(chartInstance, c2_sb_a, c2_rb_b, c2_T06);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 54);
  for (c2_i74 = 0; c2_i74 < 3; c2_i74++) {
    c2_O_6[c2_i74] = c2_T06[c2_i74 + 12];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 54);
  for (c2_i75 = 0; c2_i75 < 3; c2_i75++) {
    c2_k6[c2_i75] = c2_T06[c2_i75 + 8];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 56);
  for (c2_i76 = 0; c2_i76 < 3; c2_i76++) {
    c2_dv6[c2_i76] = c2_dv5[c2_i76];
  }

  for (c2_i77 = 0; c2_i77 < 3; c2_i77++) {
    c2_b_O_6[c2_i77] = c2_O_6[c2_i77] - c2_O_0[c2_i77];
  }

  c2_cross(chartInstance, c2_dv6, c2_b_O_6, c2_dv7);
  for (c2_i78 = 0; c2_i78 < 3; c2_i78++) {
    c2_b_k1[c2_i78] = c2_k1[c2_i78];
  }

  for (c2_i79 = 0; c2_i79 < 3; c2_i79++) {
    c2_c_O_6[c2_i79] = c2_O_6[c2_i79] - c2_O_1[c2_i79];
  }

  c2_cross(chartInstance, c2_b_k1, c2_c_O_6, c2_dv8);
  for (c2_i80 = 0; c2_i80 < 3; c2_i80++) {
    c2_b_k3[c2_i80] = c2_k3[c2_i80];
  }

  for (c2_i81 = 0; c2_i81 < 3; c2_i81++) {
    c2_d_O_6[c2_i81] = c2_O_6[c2_i81] - c2_O_3[c2_i81];
  }

  c2_cross(chartInstance, c2_b_k3, c2_d_O_6, c2_dv9);
  for (c2_i82 = 0; c2_i82 < 3; c2_i82++) {
    c2_b_k4[c2_i82] = c2_k4[c2_i82];
  }

  for (c2_i83 = 0; c2_i83 < 3; c2_i83++) {
    c2_e_O_6[c2_i83] = c2_O_6[c2_i83] - c2_O_4[c2_i83];
  }

  c2_cross(chartInstance, c2_b_k4, c2_e_O_6, c2_dv10);
  for (c2_i84 = 0; c2_i84 < 3; c2_i84++) {
    c2_b_k5[c2_i84] = c2_k5[c2_i84];
  }

  for (c2_i85 = 0; c2_i85 < 3; c2_i85++) {
    c2_f_O_6[c2_i85] = c2_O_6[c2_i85] - c2_O_5[c2_i85];
  }

  c2_cross(chartInstance, c2_b_k5, c2_f_O_6, c2_dv11);
  for (c2_i86 = 0; c2_i86 < 3; c2_i86++) {
    c2_dv12[c2_i86] = 0.0;
  }

  for (c2_i87 = 0; c2_i87 < 3; c2_i87++) {
    c2_Jacobian[c2_i87] = c2_dv7[c2_i87];
  }

  for (c2_i88 = 0; c2_i88 < 3; c2_i88++) {
    c2_Jacobian[c2_i88 + 6] = c2_dv8[c2_i88];
  }

  for (c2_i89 = 0; c2_i89 < 3; c2_i89++) {
    c2_Jacobian[c2_i89 + 12] = c2_k2[c2_i89];
  }

  for (c2_i90 = 0; c2_i90 < 3; c2_i90++) {
    c2_Jacobian[c2_i90 + 18] = c2_dv9[c2_i90];
  }

  for (c2_i91 = 0; c2_i91 < 3; c2_i91++) {
    c2_Jacobian[c2_i91 + 24] = c2_dv10[c2_i91];
  }

  for (c2_i92 = 0; c2_i92 < 3; c2_i92++) {
    c2_Jacobian[c2_i92 + 30] = c2_dv11[c2_i92];
  }

  for (c2_i93 = 0; c2_i93 < 3; c2_i93++) {
    c2_Jacobian[c2_i93 + 3] = c2_k0[c2_i93];
  }

  for (c2_i94 = 0; c2_i94 < 3; c2_i94++) {
    c2_Jacobian[c2_i94 + 9] = c2_k1[c2_i94];
  }

  for (c2_i95 = 0; c2_i95 < 3; c2_i95++) {
    c2_Jacobian[c2_i95 + 15] = c2_dv12[c2_i95];
  }

  for (c2_i96 = 0; c2_i96 < 3; c2_i96++) {
    c2_Jacobian[c2_i96 + 21] = c2_k3[c2_i96];
  }

  for (c2_i97 = 0; c2_i97 < 3; c2_i97++) {
    c2_Jacobian[c2_i97 + 27] = c2_k4[c2_i97];
  }

  for (c2_i98 = 0; c2_i98 < 3; c2_i98++) {
    c2_Jacobian[c2_i98 + 33] = c2_k5[c2_i98];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 59);
  for (c2_i99 = 0; c2_i99 < 36; c2_i99++) {
    c2_b_Jacobian[c2_i99] = c2_Jacobian[c2_i99] + 0.1;
  }

  c2_inv(chartInstance, c2_b_Jacobian, c2_dv13);
  for (c2_i100 = 0; c2_i100 < 36; c2_i100++) {
    c2_Jacob_inv[c2_i100] = c2_dv13[c2_i100];
  }

  sf_mex_printf("%s =\\n", "Jacob_inv");
  for (c2_i101 = 0; c2_i101 < 36; c2_i101++) {
    c2_u[c2_i101] = c2_Jacob_inv[c2_i101];
  }

  c2_lb_y = NULL;
  sf_mex_assign(&c2_lb_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 6, 6),
                FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c2_lb_y);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -59);
  sf_debug_symbol_scope_pop();
  for (c2_i102 = 0; c2_i102 < 36; c2_i102++) {
    (*c2_c_Jacobian)[c2_i102] = c2_Jacobian[c2_i102];
  }

  for (c2_i103 = 0; c2_i103 < 16; c2_i103++) {
    (*c2_b_T06)[c2_i103] = c2_T06[c2_i103];
  }

  for (c2_i104 = 0; c2_i104 < 16; c2_i104++) {
    (*c2_b_T03)[c2_i104] = c2_T03[c2_i104];
  }

  for (c2_i105 = 0; c2_i105 < 36; c2_i105++) {
    (*c2_b_Jacob_inv)[c2_i105] = c2_Jacob_inv[c2_i105];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_hapticsSimBlk_pd
  (SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i106;
  int32_T c2_i107;
  int32_T c2_i108;
  real_T c2_b_inData[36];
  int32_T c2_i109;
  int32_T c2_i110;
  int32_T c2_i111;
  real_T c2_u[36];
  const mxArray *c2_y = NULL;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i106 = 0;
  for (c2_i107 = 0; c2_i107 < 6; c2_i107++) {
    for (c2_i108 = 0; c2_i108 < 6; c2_i108++) {
      c2_b_inData[c2_i108 + c2_i106] = (*(real_T (*)[36])c2_inData)[c2_i108 +
        c2_i106];
    }

    c2_i106 += 6;
  }

  c2_i109 = 0;
  for (c2_i110 = 0; c2_i110 < 6; c2_i110++) {
    for (c2_i111 = 0; c2_i111 < 6; c2_i111++) {
      c2_u[c2_i111 + c2_i109] = c2_b_inData[c2_i111 + c2_i109];
    }

    c2_i109 += 6;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 6, 6), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_Jacob_inv, const char_T *c2_identifier,
  real_T c2_y[36])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Jacob_inv), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_Jacob_inv);
}

static void c2_b_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[36])
{
  real_T c2_dv14[36];
  int32_T c2_i112;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv14, 1, 0, 0U, 1, 0U, 2, 6, 6);
  for (c2_i112 = 0; c2_i112 < 36; c2_i112++) {
    c2_y[c2_i112] = c2_dv14[c2_i112];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Jacob_inv;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[36];
  int32_T c2_i113;
  int32_T c2_i114;
  int32_T c2_i115;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_Jacob_inv = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Jacob_inv), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_Jacob_inv);
  c2_i113 = 0;
  for (c2_i114 = 0; c2_i114 < 6; c2_i114++) {
    for (c2_i115 = 0; c2_i115 < 6; c2_i115++) {
      (*(real_T (*)[36])c2_outData)[c2_i115 + c2_i113] = c2_y[c2_i115 + c2_i113];
    }

    c2_i113 += 6;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i116;
  int32_T c2_i117;
  int32_T c2_i118;
  real_T c2_b_inData[16];
  int32_T c2_i119;
  int32_T c2_i120;
  int32_T c2_i121;
  real_T c2_u[16];
  const mxArray *c2_y = NULL;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i116 = 0;
  for (c2_i117 = 0; c2_i117 < 4; c2_i117++) {
    for (c2_i118 = 0; c2_i118 < 4; c2_i118++) {
      c2_b_inData[c2_i118 + c2_i116] = (*(real_T (*)[16])c2_inData)[c2_i118 +
        c2_i116];
    }

    c2_i116 += 4;
  }

  c2_i119 = 0;
  for (c2_i120 = 0; c2_i120 < 4; c2_i120++) {
    for (c2_i121 = 0; c2_i121 < 4; c2_i121++) {
      c2_u[c2_i121 + c2_i119] = c2_b_inData[c2_i121 + c2_i119];
    }

    c2_i119 += 4;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_T03, const char_T *c2_identifier, real_T
  c2_y[16])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_T03), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_T03);
}

static void c2_d_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[16])
{
  real_T c2_dv15[16];
  int32_T c2_i122;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv15, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c2_i122 = 0; c2_i122 < 16; c2_i122++) {
    c2_y[c2_i122] = c2_dv15[c2_i122];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_T03;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[16];
  int32_T c2_i123;
  int32_T c2_i124;
  int32_T c2_i125;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_T03 = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_T03), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_T03);
  c2_i123 = 0;
  for (c2_i124 = 0; c2_i124 < 4; c2_i124++) {
    for (c2_i125 = 0; c2_i125 < 4; c2_i125++) {
      (*(real_T (*)[16])c2_outData)[c2_i125 + c2_i123] = c2_y[c2_i125 + c2_i123];
    }

    c2_i123 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i126;
  real_T c2_b_inData[6];
  int32_T c2_i127;
  real_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i126 = 0; c2_i126 < 6; c2_i126++) {
    c2_b_inData[c2_i126] = (*(real_T (*)[6])c2_inData)[c2_i126];
  }

  for (c2_i127 = 0; c2_i127 < 6; c2_i127++) {
    c2_u[c2_i127] = c2_b_inData[c2_i127];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_e_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d8;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d8, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d8;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i128;
  real_T c2_b_inData[3];
  int32_T c2_i129;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i128 = 0; c2_i128 < 3; c2_i128++) {
    c2_b_inData[c2_i128] = (*(real_T (*)[3])c2_inData)[c2_i128];
  }

  for (c2_i129 = 0; c2_i129 < 3; c2_i129++) {
    c2_u[c2_i129] = c2_b_inData[c2_i129];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_f_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3])
{
  real_T c2_dv16[3];
  int32_T c2_i130;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv16, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i130 = 0; c2_i130 < 3; c2_i130++) {
    c2_y[c2_i130] = c2_dv16[c2_i130];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_k6;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i131;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_k6 = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_k6), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_k6);
  for (c2_i131 = 0; c2_i131 < 3; c2_i131++) {
    (*(real_T (*)[3])c2_outData)[c2_i131] = c2_y[c2_i131];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i132;
  int32_T c2_i133;
  int32_T c2_i134;
  real_T c2_b_inData[24];
  int32_T c2_i135;
  int32_T c2_i136;
  int32_T c2_i137;
  real_T c2_u[24];
  const mxArray *c2_y = NULL;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i132 = 0;
  for (c2_i133 = 0; c2_i133 < 4; c2_i133++) {
    for (c2_i134 = 0; c2_i134 < 6; c2_i134++) {
      c2_b_inData[c2_i134 + c2_i132] = (*(real_T (*)[24])c2_inData)[c2_i134 +
        c2_i132];
    }

    c2_i132 += 6;
  }

  c2_i135 = 0;
  for (c2_i136 = 0; c2_i136 < 4; c2_i136++) {
    for (c2_i137 = 0; c2_i137 < 6; c2_i137++) {
      c2_u[c2_i137 + c2_i135] = c2_b_inData[c2_i137 + c2_i135];
    }

    c2_i135 += 6;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 6, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_g_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[24])
{
  real_T c2_dv17[24];
  int32_T c2_i138;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv17, 1, 0, 0U, 1, 0U, 2, 6, 4);
  for (c2_i138 = 0; c2_i138 < 24; c2_i138++) {
    c2_y[c2_i138] = c2_dv17[c2_i138];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_input;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[24];
  int32_T c2_i139;
  int32_T c2_i140;
  int32_T c2_i141;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_input = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_input), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_input);
  c2_i139 = 0;
  for (c2_i140 = 0; c2_i140 < 4; c2_i140++) {
    for (c2_i141 = 0; c2_i141 < 6; c2_i141++) {
      (*(real_T (*)[24])c2_outData)[c2_i141 + c2_i139] = c2_y[c2_i141 + c2_i139];
    }

    c2_i139 += 6;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_hapticsSimBlk_pd_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[57];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i142;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 57), FALSE);
  for (c2_i142 = 0; c2_i142 < 57; c2_i142++) {
    c2_r0 = &c2_info[c2_i142];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i142);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i142);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i142);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i142);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i142);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i142);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i142);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i142);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[57])
{
  c2_info[0].context = "";
  c2_info[0].name = "mrdivide";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[0].fileTimeLo = 1310169856U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 1289552092U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[1].name = "rdivide";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[1].fileTimeLo = 1286851244U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[2].name = "eml_div";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[2].fileTimeLo = 1305350400U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "";
  c2_info[3].name = "cos";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[3].fileTimeLo = 1286851106U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[4].name = "eml_scalar_cos";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c2_info[4].fileTimeLo = 1286851122U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "";
  c2_info[5].name = "sin";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c2_info[5].fileTimeLo = 1286851150U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c2_info[6].name = "eml_scalar_sin";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c2_info[6].fileTimeLo = 1286851136U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context = "";
  c2_info[7].name = "mtimes";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[7].fileTimeLo = 1289552092U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context = "";
  c2_info[8].name = "eye";
  c2_info[8].dominantType = "double";
  c2_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m";
  c2_info[8].fileTimeLo = 1286851088U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[9].name = "eml_assert_valid_size_arg";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[9].fileTimeLo = 1286851094U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c2_info[10].name = "isinf";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c2_info[10].fileTimeLo = 1286851160U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[11].name = "eml_index_class";
  c2_info[11].dominantType = "";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[11].fileTimeLo = 1286851178U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[12].name = "intmax";
  c2_info[12].dominantType = "char";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[12].fileTimeLo = 1286851156U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[13].name = "eml_is_float_class";
  c2_info[13].dominantType = "char";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c2_info[13].fileTimeLo = 1286851182U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[14].name = "min";
  c2_info[14].dominantType = "double";
  c2_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[14].fileTimeLo = 1308779730U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[15].name = "eml_min_or_max";
  c2_info[15].dominantType = "char";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c2_info[15].fileTimeLo = 1303178612U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[16].name = "eml_scalar_eg";
  c2_info[16].dominantType = "double";
  c2_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[16].fileTimeLo = 1286851196U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[17].name = "eml_scalexp_alloc";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[17].fileTimeLo = 1286851196U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[18].name = "eml_xgemm";
  c2_info[18].dominantType = "int32";
  c2_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[18].fileTimeLo = 1299109172U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[19].name = "eml_blas_inline";
  c2_info[19].dominantType = "";
  c2_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[19].fileTimeLo = 1299109168U;
  c2_info[19].fileTimeHi = 0U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[20].name = "eml_refblas_xgemm";
  c2_info[20].dominantType = "int32";
  c2_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c2_info[20].fileTimeLo = 1299109174U;
  c2_info[20].fileTimeHi = 0U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context = "";
  c2_info[21].name = "cross";
  c2_info[21].dominantType = "double";
  c2_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c2_info[21].fileTimeLo = 1286851242U;
  c2_info[21].fileTimeHi = 0U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context = "";
  c2_info[22].name = "inv";
  c2_info[22].dominantType = "double";
  c2_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m";
  c2_info[22].fileTimeLo = 1305350400U;
  c2_info[22].fileTimeHi = 0U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
  c2_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c2_info[23].name = "eml_xgetrf";
  c2_info[23].dominantType = "int32";
  c2_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c2_info[23].fileTimeLo = 1286851206U;
  c2_info[23].fileTimeHi = 0U;
  c2_info[23].mFileTimeLo = 0U;
  c2_info[23].mFileTimeHi = 0U;
  c2_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c2_info[24].name = "eml_lapack_xgetrf";
  c2_info[24].dominantType = "int32";
  c2_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c2_info[24].fileTimeLo = 1286851210U;
  c2_info[24].fileTimeHi = 0U;
  c2_info[24].mFileTimeLo = 0U;
  c2_info[24].mFileTimeHi = 0U;
  c2_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c2_info[25].name = "eml_matlab_zgetrf";
  c2_info[25].dominantType = "int32";
  c2_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[25].fileTimeLo = 1302721394U;
  c2_info[25].fileTimeHi = 0U;
  c2_info[25].mFileTimeLo = 0U;
  c2_info[25].mFileTimeHi = 0U;
  c2_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[26].name = "realmin";
  c2_info[26].dominantType = "char";
  c2_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[26].fileTimeLo = 1286851168U;
  c2_info[26].fileTimeHi = 0U;
  c2_info[26].mFileTimeLo = 0U;
  c2_info[26].mFileTimeHi = 0U;
  c2_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[27].name = "mpower";
  c2_info[27].dominantType = "double";
  c2_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[27].fileTimeLo = 1286851242U;
  c2_info[27].fileTimeHi = 0U;
  c2_info[27].mFileTimeLo = 0U;
  c2_info[27].mFileTimeHi = 0U;
  c2_info[28].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[28].name = "power";
  c2_info[28].dominantType = "double";
  c2_info[28].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[28].fileTimeLo = 1294100344U;
  c2_info[28].fileTimeHi = 0U;
  c2_info[28].mFileTimeLo = 0U;
  c2_info[28].mFileTimeHi = 0U;
  c2_info[29].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[29].name = "eml_scalar_floor";
  c2_info[29].dominantType = "double";
  c2_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c2_info[29].fileTimeLo = 1286851126U;
  c2_info[29].fileTimeHi = 0U;
  c2_info[29].mFileTimeLo = 0U;
  c2_info[29].mFileTimeHi = 0U;
  c2_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[30].name = "eps";
  c2_info[30].dominantType = "char";
  c2_info[30].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[30].fileTimeLo = 1286851086U;
  c2_info[30].fileTimeHi = 0U;
  c2_info[30].mFileTimeLo = 0U;
  c2_info[30].mFileTimeHi = 0U;
  c2_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[31].name = "colon";
  c2_info[31].dominantType = "int32";
  c2_info[31].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[31].fileTimeLo = 1286851238U;
  c2_info[31].fileTimeHi = 0U;
  c2_info[31].mFileTimeLo = 0U;
  c2_info[31].mFileTimeHi = 0U;
  c2_info[32].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[32].name = "floor";
  c2_info[32].dominantType = "double";
  c2_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[32].fileTimeLo = 1286851142U;
  c2_info[32].fileTimeHi = 0U;
  c2_info[32].mFileTimeLo = 0U;
  c2_info[32].mFileTimeHi = 0U;
  c2_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c2_info[33].name = "intmin";
  c2_info[33].dominantType = "char";
  c2_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c2_info[33].fileTimeLo = 1286851156U;
  c2_info[33].fileTimeHi = 0U;
  c2_info[33].mFileTimeLo = 0U;
  c2_info[33].mFileTimeHi = 0U;
  c2_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[34].name = "eml_index_plus";
  c2_info[34].dominantType = "int32";
  c2_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[34].fileTimeLo = 1286851178U;
  c2_info[34].fileTimeHi = 0U;
  c2_info[34].mFileTimeLo = 0U;
  c2_info[34].mFileTimeHi = 0U;
  c2_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[35].name = "eml_index_minus";
  c2_info[35].dominantType = "int32";
  c2_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[35].fileTimeLo = 1286851178U;
  c2_info[35].fileTimeHi = 0U;
  c2_info[35].mFileTimeLo = 0U;
  c2_info[35].mFileTimeHi = 0U;
  c2_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[36].name = "eml_index_times";
  c2_info[36].dominantType = "int32";
  c2_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[36].fileTimeLo = 1286851180U;
  c2_info[36].fileTimeHi = 0U;
  c2_info[36].mFileTimeLo = 0U;
  c2_info[36].mFileTimeHi = 0U;
  c2_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[37].name = "eml_ixamax";
  c2_info[37].dominantType = "int32";
  c2_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c2_info[37].fileTimeLo = 1299109170U;
  c2_info[37].fileTimeHi = 0U;
  c2_info[37].mFileTimeLo = 0U;
  c2_info[37].mFileTimeHi = 0U;
  c2_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m!below_threshold";
  c2_info[38].name = "length";
  c2_info[38].dominantType = "double";
  c2_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[38].fileTimeLo = 1303178606U;
  c2_info[38].fileTimeHi = 0U;
  c2_info[38].mFileTimeLo = 0U;
  c2_info[38].mFileTimeHi = 0U;
  c2_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c2_info[39].name = "eml_refblas_ixamax";
  c2_info[39].dominantType = "int32";
  c2_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c2_info[39].fileTimeLo = 1299109170U;
  c2_info[39].fileTimeHi = 0U;
  c2_info[39].mFileTimeLo = 0U;
  c2_info[39].mFileTimeHi = 0U;
  c2_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c2_info[40].name = "eml_xcabs1";
  c2_info[40].dominantType = "double";
  c2_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c2_info[40].fileTimeLo = 1286851106U;
  c2_info[40].fileTimeHi = 0U;
  c2_info[40].mFileTimeLo = 0U;
  c2_info[40].mFileTimeHi = 0U;
  c2_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c2_info[41].name = "abs";
  c2_info[41].dominantType = "double";
  c2_info[41].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[41].fileTimeLo = 1286851094U;
  c2_info[41].fileTimeHi = 0U;
  c2_info[41].mFileTimeLo = 0U;
  c2_info[41].mFileTimeHi = 0U;
  c2_info[42].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[42].name = "eml_scalar_abs";
  c2_info[42].dominantType = "double";
  c2_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c2_info[42].fileTimeLo = 1286851112U;
  c2_info[42].fileTimeHi = 0U;
  c2_info[42].mFileTimeLo = 0U;
  c2_info[42].mFileTimeHi = 0U;
  c2_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[43].name = "eml_xswap";
  c2_info[43].dominantType = "int32";
  c2_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c2_info[43].fileTimeLo = 1299109178U;
  c2_info[43].fileTimeHi = 0U;
  c2_info[43].mFileTimeLo = 0U;
  c2_info[43].mFileTimeHi = 0U;
  c2_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c2_info[44].name = "eml_refblas_xswap";
  c2_info[44].dominantType = "int32";
  c2_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c2_info[44].fileTimeLo = 1299109186U;
  c2_info[44].fileTimeHi = 0U;
  c2_info[44].mFileTimeLo = 0U;
  c2_info[44].mFileTimeHi = 0U;
  c2_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c2_info[45].name = "eml_xgeru";
  c2_info[45].dominantType = "int32";
  c2_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c2_info[45].fileTimeLo = 1299109174U;
  c2_info[45].fileTimeHi = 0U;
  c2_info[45].mFileTimeLo = 0U;
  c2_info[45].mFileTimeHi = 0U;
  c2_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c2_info[46].name = "eml_xger";
  c2_info[46].dominantType = "int32";
  c2_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c2_info[46].fileTimeLo = 1299109174U;
  c2_info[46].fileTimeHi = 0U;
  c2_info[46].mFileTimeLo = 0U;
  c2_info[46].mFileTimeHi = 0U;
  c2_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c2_info[47].name = "eml_refblas_xger";
  c2_info[47].dominantType = "int32";
  c2_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c2_info[47].fileTimeLo = 1299109176U;
  c2_info[47].fileTimeHi = 0U;
  c2_info[47].mFileTimeLo = 0U;
  c2_info[47].mFileTimeHi = 0U;
  c2_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c2_info[48].name = "eml_refblas_xgerx";
  c2_info[48].dominantType = "int32";
  c2_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c2_info[48].fileTimeLo = 1299109178U;
  c2_info[48].fileTimeHi = 0U;
  c2_info[48].mFileTimeLo = 0U;
  c2_info[48].mFileTimeHi = 0U;
  c2_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c2_info[49].name = "eml_ipiv2perm";
  c2_info[49].dominantType = "int32";
  c2_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_ipiv2perm.m";
  c2_info[49].fileTimeLo = 1286851182U;
  c2_info[49].fileTimeHi = 0U;
  c2_info[49].mFileTimeLo = 0U;
  c2_info[49].mFileTimeHi = 0U;
  c2_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!invNxN";
  c2_info[50].name = "eml_xtrsm";
  c2_info[50].dominantType = "int32";
  c2_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xtrsm.m";
  c2_info[50].fileTimeLo = 1299109178U;
  c2_info[50].fileTimeHi = 0U;
  c2_info[50].mFileTimeLo = 0U;
  c2_info[50].mFileTimeHi = 0U;
  c2_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xtrsm.m";
  c2_info[51].name = "eml_refblas_xtrsm";
  c2_info[51].dominantType = "int32";
  c2_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xtrsm.m";
  c2_info[51].fileTimeLo = 1299109186U;
  c2_info[51].fileTimeHi = 0U;
  c2_info[51].mFileTimeLo = 0U;
  c2_info[51].mFileTimeHi = 0U;
  c2_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c2_info[52].name = "norm";
  c2_info[52].dominantType = "double";
  c2_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c2_info[52].fileTimeLo = 1286851226U;
  c2_info[52].fileTimeHi = 0U;
  c2_info[52].mFileTimeLo = 0U;
  c2_info[52].mFileTimeHi = 0U;
  c2_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c2_info[53].name = "isnan";
  c2_info[53].dominantType = "double";
  c2_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[53].fileTimeLo = 1286851160U;
  c2_info[53].fileTimeHi = 0U;
  c2_info[53].mFileTimeLo = 0U;
  c2_info[53].mFileTimeHi = 0U;
  c2_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!mat1norm";
  c2_info[54].name = "eml_guarded_nan";
  c2_info[54].dominantType = "char";
  c2_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_guarded_nan.m";
  c2_info[54].fileTimeLo = 1286851176U;
  c2_info[54].fileTimeHi = 0U;
  c2_info[54].mFileTimeLo = 0U;
  c2_info[54].mFileTimeHi = 0U;
  c2_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c2_info[55].name = "eml_warning";
  c2_info[55].dominantType = "char";
  c2_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c2_info[55].fileTimeLo = 1286851202U;
  c2_info[55].fileTimeHi = 0U;
  c2_info[55].mFileTimeLo = 0U;
  c2_info[55].mFileTimeHi = 0U;
  c2_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/inv.m!checkcond";
  c2_info[56].name = "eml_flt2str";
  c2_info[56].dominantType = "double";
  c2_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_flt2str.m";
  c2_info[56].fileTimeLo = 1286851176U;
  c2_info[56].fileTimeHi = 0U;
  c2_info[56].mFileTimeLo = 0U;
  c2_info[56].mFileTimeHi = 0U;
}

static real_T c2_mrdivide(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A, real_T c2_B)
{
  real_T c2_x;
  real_T c2_b_y;
  real_T c2_b_x;
  real_T c2_c_y;
  c2_x = c2_A;
  c2_b_y = c2_B;
  c2_b_x = c2_x;
  c2_c_y = c2_b_y;
  return c2_b_x / c2_c_y;
}

static void c2_eml_scalar_eg(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance)
{
}

static void c2_eml_xgemm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[16], real_T c2_C[16], real_T c2_b_C[16])
{
  int32_T c2_i143;
  int32_T c2_i144;
  real_T c2_b_A[16];
  int32_T c2_i145;
  real_T c2_b_B[16];
  for (c2_i143 = 0; c2_i143 < 16; c2_i143++) {
    c2_b_C[c2_i143] = c2_C[c2_i143];
  }

  for (c2_i144 = 0; c2_i144 < 16; c2_i144++) {
    c2_b_A[c2_i144] = c2_A[c2_i144];
  }

  for (c2_i145 = 0; c2_i145 < 16; c2_i145++) {
    c2_b_B[c2_i145] = c2_B[c2_i145];
  }

  c2_b_eml_xgemm(chartInstance, c2_b_A, c2_b_B, c2_b_C);
}

static void c2_cross(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance, real_T
                     c2_a[3], real_T c2_b[3], real_T c2_c[3])
{
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_y;
  real_T c2_c_a;
  real_T c2_c_b;
  real_T c2_b_y;
  real_T c2_c1;
  real_T c2_d_a;
  real_T c2_d_b;
  real_T c2_c_y;
  real_T c2_e_a;
  real_T c2_e_b;
  real_T c2_d_y;
  real_T c2_c2;
  real_T c2_f_a;
  real_T c2_f_b;
  real_T c2_e_y;
  real_T c2_g_a;
  real_T c2_g_b;
  real_T c2_f_y;
  real_T c2_c3;
  c2_b_a = c2_a[1];
  c2_b_b = c2_b[2];
  c2_y = c2_b_a * c2_b_b;
  c2_c_a = c2_a[2];
  c2_c_b = c2_b[1];
  c2_b_y = c2_c_a * c2_c_b;
  c2_c1 = c2_y - c2_b_y;
  c2_d_a = c2_a[2];
  c2_d_b = c2_b[0];
  c2_c_y = c2_d_a * c2_d_b;
  c2_e_a = c2_a[0];
  c2_e_b = c2_b[2];
  c2_d_y = c2_e_a * c2_e_b;
  c2_c2 = c2_c_y - c2_d_y;
  c2_f_a = c2_a[0];
  c2_f_b = c2_b[1];
  c2_e_y = c2_f_a * c2_f_b;
  c2_g_a = c2_a[1];
  c2_g_b = c2_b[0];
  c2_f_y = c2_g_a * c2_g_b;
  c2_c3 = c2_e_y - c2_f_y;
  c2_c[0] = c2_c1;
  c2_c[1] = c2_c2;
  c2_c[2] = c2_c3;
}

static void c2_inv(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance, real_T
                   c2_x[36], real_T c2_y[36])
{
  int32_T c2_i146;
  real_T c2_b_x[36];
  int32_T c2_i147;
  int32_T c2_info;
  int32_T c2_ipiv[6];
  int32_T c2_i148;
  int32_T c2_p[6];
  int32_T c2_k;
  real_T c2_b_k;
  int32_T c2_ipk;
  int32_T c2_pipk;
  int32_T c2_c_k;
  int32_T c2_d_k;
  int32_T c2_c;
  int32_T c2_e_k;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_i149;
  int32_T c2_i;
  int32_T c2_b_i;
  real_T c2_b_a;
  real_T c2_b;
  real_T c2_b_y;
  int32_T c2_i150;
  real_T c2_c_x[36];
  int32_T c2_i151;
  real_T c2_d_x[36];
  real_T c2_n1x;
  int32_T c2_i152;
  real_T c2_c_y[36];
  real_T c2_n1xinv;
  real_T c2_c_a;
  real_T c2_b_b;
  real_T c2_d_y;
  real_T c2_rc;
  real_T c2_e_x;
  boolean_T c2_c_b;
  real_T c2_f_x;
  int32_T c2_i153;
  static char_T c2_cv0[8] = { '%', '%', '%', 'd', '.', '%', 'd', 'e' };

  char_T c2_u[8];
  const mxArray *c2_e_y = NULL;
  real_T c2_b_u;
  const mxArray *c2_f_y = NULL;
  real_T c2_c_u;
  const mxArray *c2_g_y = NULL;
  real_T c2_d_u;
  const mxArray *c2_h_y = NULL;
  char_T c2_str[14];
  int32_T c2_i154;
  char_T c2_b_str[14];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  for (c2_i146 = 0; c2_i146 < 36; c2_i146++) {
    c2_b_x[c2_i146] = c2_x[c2_i146];
  }

  for (c2_i147 = 0; c2_i147 < 36; c2_i147++) {
    c2_y[c2_i147] = 0.0;
  }

  c2_b_eml_matlab_zgetrf(chartInstance, c2_b_x, c2_ipiv, &c2_info);
  for (c2_i148 = 0; c2_i148 < 6; c2_i148++) {
    c2_p[c2_i148] = 1 + c2_i148;
  }

  for (c2_k = 0; c2_k < 5; c2_k++) {
    c2_b_k = 1.0 + (real_T)c2_k;
    c2_ipk = c2_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", c2_b_k), 1, 6, 1, 0) - 1];
    if ((real_T)c2_ipk > c2_b_k) {
      c2_pipk = c2_p[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
        ("", (real_T)c2_ipk), 1, 6, 1, 0) - 1];
      c2_p[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        (real_T)c2_ipk), 1, 6, 1, 0) - 1] = c2_p[_SFD_EML_ARRAY_BOUNDS_CHECK("",
        (int32_T)_SFD_INTEGER_CHECK("", c2_b_k), 1, 6, 1, 0) - 1];
      c2_p[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
        c2_b_k), 1, 6, 1, 0) - 1] = c2_pipk;
    }
  }

  for (c2_c_k = 1; c2_c_k < 7; c2_c_k++) {
    c2_d_k = c2_c_k;
    c2_c = c2_p[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_d_k), 1, 6, 1, 0) - 1];
    c2_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_d_k), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
            (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c), 1, 6, 2, 0) - 1)) - 1]
      = 1.0;
    c2_e_k = c2_d_k;
    for (c2_j = c2_e_k; c2_j < 7; c2_j++) {
      c2_b_j = c2_j;
      if (c2_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
             (real_T)c2_b_j), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c), 1, 6, 2, 0) - 1)) -
          1] != 0.0) {
        c2_a = c2_b_j;
        c2_i149 = c2_a;
        for (c2_i = c2_i149 + 1; c2_i < 7; c2_i++) {
          c2_b_i = c2_i;
          c2_b_a = c2_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 6, 1, 0) + 6 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_c), 1, 6, 2, 0) - 1)) - 1];
          c2_b = c2_b_x[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 6, 1, 0) + 6 *
                         (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_b_j), 1, 6, 2, 0) - 1)) - 1];
          c2_b_y = c2_b_a * c2_b;
          c2_y[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                  (real_T)c2_b_i), 1, 6, 1, 0) + 6 *
                (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                   (real_T)c2_c), 1, 6, 2, 0) - 1)) - 1] = c2_y
            [(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
                (real_T)c2_b_i), 1, 6, 1, 0) + 6 * (_SFD_EML_ARRAY_BOUNDS_CHECK(
                "", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_c), 1, 6, 2, 0) -
               1)) - 1] - c2_b_y;
        }
      }
    }
  }

  for (c2_i150 = 0; c2_i150 < 36; c2_i150++) {
    c2_c_x[c2_i150] = c2_b_x[c2_i150];
  }

  c2_b_eml_xtrsm(chartInstance, c2_c_x, c2_y);
  for (c2_i151 = 0; c2_i151 < 36; c2_i151++) {
    c2_d_x[c2_i151] = c2_x[c2_i151];
  }

  c2_n1x = c2_norm(chartInstance, c2_d_x);
  for (c2_i152 = 0; c2_i152 < 36; c2_i152++) {
    c2_c_y[c2_i152] = c2_y[c2_i152];
  }

  c2_n1xinv = c2_norm(chartInstance, c2_c_y);
  c2_c_a = c2_n1x;
  c2_b_b = c2_n1xinv;
  c2_d_y = c2_c_a * c2_b_b;
  c2_rc = 1.0 / c2_d_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c2_n1x == 0.0) {
    guard2 = TRUE;
  } else if (c2_n1xinv == 0.0) {
    guard2 = TRUE;
  } else if (c2_rc == 0.0) {
    guard1 = TRUE;
  } else {
    c2_e_x = c2_rc;
    c2_c_b = muDoubleScalarIsNaN(c2_e_x);
    guard3 = FALSE;
    if (c2_c_b) {
      guard3 = TRUE;
    } else {
      if (c2_rc < 2.2204460492503131E-16) {
        guard3 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      c2_f_x = c2_rc;
      for (c2_i153 = 0; c2_i153 < 8; c2_i153++) {
        c2_u[c2_i153] = c2_cv0[c2_i153];
      }

      c2_e_y = NULL;
      sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 8),
                    FALSE);
      c2_b_u = 14.0;
      c2_f_y = NULL;
      sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c2_c_u = 6.0;
      c2_g_y = NULL;
      sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c2_d_u = c2_f_x;
      c2_h_y = NULL;
      sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0),
                    FALSE);
      c2_h_emlrt_marshallIn(chartInstance, sf_mex_call_debug("sprintf", 1U, 2U,
        14, sf_mex_call_debug("sprintf", 1U, 3U, 14, c2_e_y, 14, c2_f_y, 14,
        c2_g_y), 14, c2_h_y), "sprintf", c2_str);
      for (c2_i154 = 0; c2_i154 < 14; c2_i154++) {
        c2_b_str[c2_i154] = c2_str[c2_i154];
      }

      c2_b_eml_warning(chartInstance, c2_b_str);
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c2_eml_warning(chartInstance);
  }
}

static void c2_eps(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance)
{
}

static void c2_eml_matlab_zgetrf(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, real_T c2_A[36], real_T c2_b_A[36], int32_T c2_ipiv[6],
  int32_T *c2_info)
{
  int32_T c2_i155;
  for (c2_i155 = 0; c2_i155 < 36; c2_i155++) {
    c2_b_A[c2_i155] = c2_A[c2_i155];
  }

  c2_b_eml_matlab_zgetrf(chartInstance, c2_b_A, c2_ipiv, c2_info);
}

static int32_T c2_eml_ixamax(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  int32_T c2_n, real_T c2_x[36], int32_T c2_ix0)
{
  int32_T c2_idxmax;
  int32_T c2_b_n;
  int32_T c2_b_ix0;
  int32_T c2_c_n;
  int32_T c2_c_ix0;
  int32_T c2_ix;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_y;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_b_y;
  real_T c2_smax;
  int32_T c2_loop_ub;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_a;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_c_y;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_d_y;
  real_T c2_s;
  c2_b_n = c2_n;
  c2_b_ix0 = c2_ix0;
  c2_c_n = c2_b_n;
  c2_c_ix0 = c2_b_ix0;
  if ((real_T)c2_c_n < 1.0) {
    c2_idxmax = 0;
  } else {
    c2_idxmax = 1;
    if ((real_T)c2_c_n > 1.0) {
      c2_ix = c2_c_ix0;
      c2_b_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_ix), 1, 36, 1, 0) - 1];
      c2_c_x = c2_b_x;
      c2_d_x = c2_c_x;
      c2_y = muDoubleScalarAbs(c2_d_x);
      c2_e_x = 0.0;
      c2_f_x = c2_e_x;
      c2_b_y = muDoubleScalarAbs(c2_f_x);
      c2_smax = c2_y + c2_b_y;
      c2_loop_ub = c2_c_n;
      for (c2_k = 2; c2_k <= c2_loop_ub; c2_k++) {
        c2_b_k = c2_k;
        c2_a = c2_ix + 1;
        c2_ix = c2_a;
        c2_g_x = c2_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 36, 1, 0) - 1];
        c2_h_x = c2_g_x;
        c2_i_x = c2_h_x;
        c2_c_y = muDoubleScalarAbs(c2_i_x);
        c2_j_x = 0.0;
        c2_k_x = c2_j_x;
        c2_d_y = muDoubleScalarAbs(c2_k_x);
        c2_s = c2_c_y + c2_d_y;
        if (c2_s > c2_smax) {
          c2_idxmax = c2_b_k;
          c2_smax = c2_s;
        }
      }
    }
  }

  return c2_idxmax;
}

static void c2_eml_xtrsm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A[36], real_T c2_B[36], real_T c2_b_B[36])
{
  int32_T c2_i156;
  int32_T c2_i157;
  real_T c2_b_A[36];
  for (c2_i156 = 0; c2_i156 < 36; c2_i156++) {
    c2_b_B[c2_i156] = c2_B[c2_i156];
  }

  for (c2_i157 = 0; c2_i157 < 36; c2_i157++) {
    c2_b_A[c2_i157] = c2_A[c2_i157];
  }

  c2_b_eml_xtrsm(chartInstance, c2_b_A, c2_b_B);
}

static real_T c2_norm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance, real_T
                      c2_x[36])
{
  real_T c2_y;
  int32_T c2_j;
  real_T c2_b_j;
  real_T c2_s;
  int32_T c2_i;
  real_T c2_b_i;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_b_y;
  real_T c2_d_x;
  boolean_T c2_b;
  boolean_T exitg1;
  c2_y = 0.0;
  c2_j = 0;
  exitg1 = 0U;
  while ((exitg1 == 0U) && (c2_j < 6)) {
    c2_b_j = 1.0 + (real_T)c2_j;
    c2_s = 0.0;
    for (c2_i = 0; c2_i < 6; c2_i++) {
      c2_b_i = 1.0 + (real_T)c2_i;
      c2_b_x = c2_x[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
                      ("", c2_b_i), 1, 6, 1, 0) + 6 *
                     (_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c2_b_j), 1, 6, 2, 0) - 1)) - 1];
      c2_c_x = c2_b_x;
      c2_b_y = muDoubleScalarAbs(c2_c_x);
      c2_s += c2_b_y;
    }

    c2_d_x = c2_s;
    c2_b = muDoubleScalarIsNaN(c2_d_x);
    if (c2_b) {
      c2_y = rtNaN;
      exitg1 = 1U;
    } else {
      if (c2_s > c2_y) {
        c2_y = c2_s;
      }

      c2_j++;
    }
  }

  return c2_y;
}

static void c2_eml_warning(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance)
{
  int32_T c2_i158;
  static char_T c2_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c2_u[27];
  const mxArray *c2_y = NULL;
  for (c2_i158 = 0; c2_i158 < 27; c2_i158++) {
    c2_u[c2_i158] = c2_varargin_1[c2_i158];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 27), FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c2_y));
}

static void c2_b_eml_warning(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  char_T c2_varargin_2[14])
{
  int32_T c2_i159;
  static char_T c2_varargin_1[33] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'i', 'l', 'l', 'C', 'o', 'n', 'd', 'i', 't', 'i',
    'o', 'n', 'e', 'd', 'M', 'a', 't', 'r', 'i', 'x' };

  char_T c2_u[33];
  const mxArray *c2_y = NULL;
  int32_T c2_i160;
  char_T c2_b_u[14];
  const mxArray *c2_b_y = NULL;
  for (c2_i159 = 0; c2_i159 < 33; c2_i159++) {
    c2_u[c2_i159] = c2_varargin_1[c2_i159];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 33), FALSE);
  for (c2_i160 = 0; c2_i160 < 14; c2_i160++) {
    c2_b_u[c2_i160] = c2_varargin_2[c2_i160];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 14),
                FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
    14, c2_y, 14, c2_b_y));
}

static void c2_h_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_sprintf, const char_T *c2_identifier, char_T
  c2_y[14])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_sprintf), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_sprintf);
}

static void c2_i_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  char_T c2_y[14])
{
  char_T c2_cv1[14];
  int32_T c2_i161;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                14);
  for (c2_i161 = 0; c2_i161 < 14; c2_i161++) {
    c2_y[c2_i161] = c2_cv1[c2_i161];
  }

  sf_mex_destroy(&c2_u);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_j_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i162;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i162, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i162;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_k_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_hapticsSimBlk_pd, const
  char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_hapticsSimBlk_pd), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_hapticsSimBlk_pd);
  return c2_y;
}

static uint8_T c2_l_emlrt_marshallIn(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_eml_xgemm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A[16], real_T c2_B[16], real_T c2_C[16])
{
  int32_T c2_i163;
  int32_T c2_i164;
  int32_T c2_i165;
  int32_T c2_i166;
  int32_T c2_i167;
  for (c2_i163 = 0; c2_i163 < 4; c2_i163++) {
    c2_i164 = 0;
    for (c2_i165 = 0; c2_i165 < 4; c2_i165++) {
      c2_C[c2_i164 + c2_i163] = 0.0;
      c2_i166 = 0;
      for (c2_i167 = 0; c2_i167 < 4; c2_i167++) {
        c2_C[c2_i164 + c2_i163] += c2_A[c2_i166 + c2_i163] * c2_B[c2_i167 +
          c2_i164];
        c2_i166 += 4;
      }

      c2_i164 += 4;
    }
  }
}

static void c2_b_eml_matlab_zgetrf(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance, real_T c2_A[36], int32_T c2_ipiv[6], int32_T *c2_info)
{
  int32_T c2_i168;
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_jm1;
  int32_T c2_b;
  int32_T c2_mmj;
  int32_T c2_b_a;
  int32_T c2_c;
  int32_T c2_b_b;
  int32_T c2_jj;
  int32_T c2_c_a;
  int32_T c2_jp1j;
  int32_T c2_d_a;
  int32_T c2_b_c;
  int32_T c2_i169;
  int32_T c2_i170;
  int32_T c2_i171;
  real_T c2_b_A[36];
  int32_T c2_e_a;
  int32_T c2_jpiv_offset;
  int32_T c2_f_a;
  int32_T c2_c_b;
  int32_T c2_jpiv;
  int32_T c2_g_a;
  int32_T c2_d_b;
  int32_T c2_c_c;
  int32_T c2_e_b;
  int32_T c2_jrow;
  int32_T c2_h_a;
  int32_T c2_f_b;
  int32_T c2_jprow;
  int32_T c2_ix0;
  int32_T c2_iy0;
  int32_T c2_b_ix0;
  int32_T c2_b_iy0;
  int32_T c2_c_ix0;
  int32_T c2_c_iy0;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_k;
  real_T c2_temp;
  int32_T c2_i_a;
  int32_T c2_j_a;
  int32_T c2_b_jp1j;
  int32_T c2_k_a;
  int32_T c2_d_c;
  int32_T c2_l_a;
  int32_T c2_g_b;
  int32_T c2_i172;
  int32_T c2_i;
  int32_T c2_b_i;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_h_b;
  int32_T c2_e_c;
  int32_T c2_m_a;
  int32_T c2_f_c;
  int32_T c2_n_a;
  int32_T c2_g_c;
  int32_T c2_m;
  int32_T c2_n;
  int32_T c2_d_ix0;
  int32_T c2_d_iy0;
  int32_T c2_ia0;
  int32_T c2_b_m;
  int32_T c2_b_n;
  int32_T c2_e_ix0;
  int32_T c2_e_iy0;
  int32_T c2_b_ia0;
  int32_T c2_c_m;
  int32_T c2_c_n;
  int32_T c2_f_ix0;
  int32_T c2_f_iy0;
  int32_T c2_c_ia0;
  int32_T c2_d_m;
  int32_T c2_d_n;
  int32_T c2_g_ix0;
  int32_T c2_g_iy0;
  int32_T c2_d_ia0;
  int32_T c2_e_m;
  int32_T c2_e_n;
  int32_T c2_h_ix0;
  int32_T c2_h_iy0;
  int32_T c2_e_ia0;
  int32_T c2_ixstart;
  int32_T c2_o_a;
  int32_T c2_jA;
  int32_T c2_jy;
  int32_T c2_loop_ub;
  int32_T c2_c_j;
  real_T c2_yjy;
  real_T c2_b_temp;
  int32_T c2_b_ix;
  int32_T c2_i_b;
  int32_T c2_i173;
  int32_T c2_p_a;
  int32_T c2_j_b;
  int32_T c2_i174;
  int32_T c2_ijA;
  int32_T c2_b_ijA;
  int32_T c2_q_a;
  int32_T c2_r_a;
  int32_T c2_s_a;
  c2_eps(chartInstance);
  for (c2_i168 = 0; c2_i168 < 6; c2_i168++) {
    c2_ipiv[c2_i168] = 1 + c2_i168;
  }

  *c2_info = 0;
  for (c2_j = 1; c2_j < 6; c2_j++) {
    c2_b_j = c2_j;
    c2_a = c2_b_j - 1;
    c2_jm1 = c2_a;
    c2_b = c2_b_j;
    c2_mmj = 6 - c2_b;
    c2_b_a = c2_jm1;
    c2_c = c2_b_a * 7;
    c2_b_b = c2_c + 1;
    c2_jj = c2_b_b;
    c2_c_a = c2_jj + 1;
    c2_jp1j = c2_c_a;
    c2_d_a = c2_mmj;
    c2_b_c = c2_d_a;
    c2_i169 = 0;
    for (c2_i170 = 0; c2_i170 < 6; c2_i170++) {
      for (c2_i171 = 0; c2_i171 < 6; c2_i171++) {
        c2_b_A[c2_i171 + c2_i169] = c2_A[c2_i171 + c2_i169];
      }

      c2_i169 += 6;
    }

    c2_e_a = c2_eml_ixamax(chartInstance, c2_b_c + 1, c2_b_A, c2_jj) - 1;
    c2_jpiv_offset = c2_e_a;
    c2_f_a = c2_jj;
    c2_c_b = c2_jpiv_offset;
    c2_jpiv = c2_f_a + c2_c_b;
    if (c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_jpiv), 1, 36, 1, 0) - 1] != 0.0) {
      if ((real_T)c2_jpiv_offset != 0.0) {
        c2_g_a = c2_b_j;
        c2_d_b = c2_jpiv_offset;
        c2_c_c = c2_g_a + c2_d_b;
        c2_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_j), 1, 6, 1, 0) - 1] = c2_c_c;
        c2_e_b = c2_jm1 + 1;
        c2_jrow = c2_e_b;
        c2_h_a = c2_jrow;
        c2_f_b = c2_jpiv_offset;
        c2_jprow = c2_h_a + c2_f_b;
        c2_ix0 = c2_jrow;
        c2_iy0 = c2_jprow;
        c2_b_ix0 = c2_ix0;
        c2_b_iy0 = c2_iy0;
        c2_c_ix0 = c2_b_ix0;
        c2_c_iy0 = c2_b_iy0;
        c2_ix = c2_c_ix0;
        c2_iy = c2_c_iy0;
        for (c2_k = 1; c2_k < 7; c2_k++) {
          c2_temp = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c2_ix), 1, 36, 1, 0) - 1];
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_ix), 1, 36, 1, 0) - 1] = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK
            ("", (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_iy), 1, 36, 1, 0) -
            1];
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_iy), 1, 36, 1, 0) - 1] = c2_temp;
          c2_i_a = c2_ix + 6;
          c2_ix = c2_i_a;
          c2_j_a = c2_iy + 6;
          c2_iy = c2_j_a;
        }
      }

      c2_b_jp1j = c2_jp1j;
      c2_k_a = c2_mmj;
      c2_d_c = c2_k_a;
      c2_l_a = c2_jp1j;
      c2_g_b = c2_d_c - 1;
      c2_i172 = c2_l_a + c2_g_b;
      for (c2_i = c2_b_jp1j; c2_i <= c2_i172; c2_i++) {
        c2_b_i = c2_i;
        c2_x = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_b_i), 1, 36, 1, 0) - 1];
        c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_jj), 1, 36, 1, 0) - 1];
        c2_z = c2_x / c2_y;
        c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_b_i), 1, 36, 1, 0) - 1] = c2_z;
      }
    } else {
      *c2_info = c2_b_j;
    }

    c2_h_b = c2_b_j;
    c2_e_c = 6 - c2_h_b;
    c2_m_a = c2_jj;
    c2_f_c = c2_m_a;
    c2_n_a = c2_jj;
    c2_g_c = c2_n_a;
    c2_m = c2_mmj;
    c2_n = c2_e_c;
    c2_d_ix0 = c2_jp1j;
    c2_d_iy0 = c2_f_c + 6;
    c2_ia0 = c2_g_c + 7;
    c2_b_m = c2_m;
    c2_b_n = c2_n;
    c2_e_ix0 = c2_d_ix0;
    c2_e_iy0 = c2_d_iy0;
    c2_b_ia0 = c2_ia0;
    c2_c_m = c2_b_m;
    c2_c_n = c2_b_n;
    c2_f_ix0 = c2_e_ix0;
    c2_f_iy0 = c2_e_iy0;
    c2_c_ia0 = c2_b_ia0;
    c2_d_m = c2_c_m;
    c2_d_n = c2_c_n;
    c2_g_ix0 = c2_f_ix0;
    c2_g_iy0 = c2_f_iy0;
    c2_d_ia0 = c2_c_ia0;
    c2_e_m = c2_d_m;
    c2_e_n = c2_d_n;
    c2_h_ix0 = c2_g_ix0;
    c2_h_iy0 = c2_g_iy0;
    c2_e_ia0 = c2_d_ia0;
    c2_ixstart = c2_h_ix0;
    c2_o_a = c2_e_ia0 - 1;
    c2_jA = c2_o_a;
    c2_jy = c2_h_iy0;
    c2_loop_ub = c2_e_n;
    for (c2_c_j = 1; c2_c_j <= c2_loop_ub; c2_c_j++) {
      c2_yjy = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c2_jy), 1, 36, 1, 0) - 1];
      if (c2_yjy != 0.0) {
        c2_b_temp = -c2_yjy;
        c2_b_ix = c2_ixstart;
        c2_i_b = c2_jA;
        c2_i173 = c2_i_b;
        c2_p_a = c2_e_m;
        c2_j_b = c2_jA;
        c2_i174 = c2_p_a + c2_j_b;
        for (c2_ijA = c2_i173 + 1; c2_ijA <= c2_i174; c2_ijA++) {
          c2_b_ijA = c2_ijA;
          c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_ijA), 1, 36, 1, 0) - 1] =
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_ijA), 1, 36, 1, 0) - 1] +
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_ix), 1, 36, 1, 0) - 1] * c2_b_temp;
          c2_q_a = c2_b_ix + 1;
          c2_b_ix = c2_q_a;
        }
      }

      c2_r_a = c2_jy + 6;
      c2_jy = c2_r_a;
      c2_s_a = c2_jA + 6;
      c2_jA = c2_s_a;
    }
  }

  if ((real_T)*c2_info == 0.0) {
    if (!(c2_A[35] != 0.0)) {
      *c2_info = 6;
    }
  }
}

static void c2_b_eml_xtrsm(SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance,
  real_T c2_A[36], real_T c2_B[36])
{
  int32_T c2_j;
  int32_T c2_b_j;
  int32_T c2_a;
  int32_T c2_c;
  int32_T c2_b;
  int32_T c2_b_c;
  int32_T c2_b_b;
  int32_T c2_jBcol;
  int32_T c2_k;
  int32_T c2_b_k;
  int32_T c2_b_a;
  int32_T c2_c_c;
  int32_T c2_c_b;
  int32_T c2_d_c;
  int32_T c2_d_b;
  int32_T c2_kAcol;
  int32_T c2_c_a;
  int32_T c2_e_b;
  int32_T c2_e_c;
  int32_T c2_d_a;
  int32_T c2_f_b;
  int32_T c2_f_c;
  int32_T c2_e_a;
  int32_T c2_g_b;
  int32_T c2_g_c;
  int32_T c2_f_a;
  int32_T c2_h_b;
  int32_T c2_h_c;
  real_T c2_x;
  real_T c2_y;
  real_T c2_z;
  int32_T c2_g_a;
  int32_T c2_i175;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_h_a;
  int32_T c2_i_b;
  int32_T c2_i_c;
  int32_T c2_i_a;
  int32_T c2_j_b;
  int32_T c2_j_c;
  int32_T c2_j_a;
  int32_T c2_k_b;
  int32_T c2_k_c;
  int32_T c2_k_a;
  int32_T c2_l_b;
  int32_T c2_l_c;
  for (c2_j = 1; c2_j < 7; c2_j++) {
    c2_b_j = c2_j;
    c2_a = c2_b_j;
    c2_c = c2_a;
    c2_b = c2_c - 1;
    c2_b_c = 6 * c2_b;
    c2_b_b = c2_b_c;
    c2_jBcol = c2_b_b;
    for (c2_k = 6; c2_k > 0; c2_k--) {
      c2_b_k = c2_k;
      c2_b_a = c2_b_k;
      c2_c_c = c2_b_a;
      c2_c_b = c2_c_c - 1;
      c2_d_c = 6 * c2_c_b;
      c2_d_b = c2_d_c;
      c2_kAcol = c2_d_b;
      c2_c_a = c2_b_k;
      c2_e_b = c2_jBcol;
      c2_e_c = c2_c_a + c2_e_b;
      if (c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_e_c), 1, 36, 1, 0) - 1] != 0.0) {
        c2_d_a = c2_b_k;
        c2_f_b = c2_jBcol;
        c2_f_c = c2_d_a + c2_f_b;
        c2_e_a = c2_b_k;
        c2_g_b = c2_jBcol;
        c2_g_c = c2_e_a + c2_g_b;
        c2_f_a = c2_b_k;
        c2_h_b = c2_kAcol;
        c2_h_c = c2_f_a + c2_h_b;
        c2_x = c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_g_c), 1, 36, 1, 0) - 1];
        c2_y = c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c2_h_c), 1, 36, 1, 0) - 1];
        c2_z = c2_x / c2_y;
        c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c2_f_c), 1, 36, 1, 0) - 1] = c2_z;
        c2_g_a = c2_b_k;
        c2_i175 = c2_g_a;
        for (c2_i = 1; c2_i <= c2_i175 - 1; c2_i++) {
          c2_b_i = c2_i;
          c2_h_a = c2_b_i;
          c2_i_b = c2_jBcol;
          c2_i_c = c2_h_a + c2_i_b;
          c2_i_a = c2_b_i;
          c2_j_b = c2_jBcol;
          c2_j_c = c2_i_a + c2_j_b;
          c2_j_a = c2_b_k;
          c2_k_b = c2_jBcol;
          c2_k_c = c2_j_a + c2_k_b;
          c2_k_a = c2_b_i;
          c2_l_b = c2_kAcol;
          c2_l_c = c2_k_a + c2_l_b;
          c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_i_c), 1, 36, 1, 0) - 1] =
            c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_j_c), 1, 36, 1, 0) - 1] -
            c2_B[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_k_c), 1, 36, 1, 0) - 1] *
            c2_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_l_c), 1, 36, 1, 0) - 1];
        }
      }
    }
  }
}

static void init_dsm_address_info(SFc2_hapticsSimBlk_pdInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_hapticsSimBlk_pd_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1184770174U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2781239294U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2276831663U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3980800246U);
}

mxArray *sf_c2_hapticsSimBlk_pd_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("6EabRskunBDRTVlTqRKkZD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c2_hapticsSimBlk_pd(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[13],T\"Jacob_inv\",},{M[1],M[5],T\"Jacobian\",},{M[1],M[12],T\"T03\",},{M[1],M[11],T\"T06\",},{M[8],M[0],T\"is_active_c2_hapticsSimBlk_pd\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_hapticsSimBlk_pd_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
    chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hapticsSimBlk_pdMachineNumber_,
           2,
           1,
           1,
           5,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_hapticsSimBlk_pdMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_hapticsSimBlk_pdMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_hapticsSimBlk_pdMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"q");
          _SFD_SET_DATA_PROPS(1,2,0,1,"Jacobian");
          _SFD_SET_DATA_PROPS(2,2,0,1,"T06");
          _SFD_SET_DATA_PROPS(3,2,0,1,"T03");
          _SFD_SET_DATA_PROPS(4,2,0,1,"Jacob_inv");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,3680);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)
            c2_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          real_T (*c2_q)[6];
          real_T (*c2_Jacobian)[36];
          real_T (*c2_T06)[16];
          real_T (*c2_T03)[16];
          real_T (*c2_Jacob_inv)[36];
          c2_Jacob_inv = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S,
            4);
          c2_T03 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 3);
          c2_T06 = (real_T (*)[16])ssGetOutputPortSignal(chartInstance->S, 2);
          c2_Jacobian = (real_T (*)[36])ssGetOutputPortSignal(chartInstance->S,
            1);
          c2_q = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_q);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_Jacobian);
          _SFD_SET_DATA_VALUE_PTR(2U, *c2_T06);
          _SFD_SET_DATA_VALUE_PTR(3U, *c2_T03);
          _SFD_SET_DATA_VALUE_PTR(4U, *c2_Jacob_inv);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_hapticsSimBlk_pdMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c2_hapticsSimBlk_pd(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_hapticsSimBlk_pdInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_hapticsSimBlk_pd((SFc2_hapticsSimBlk_pdInstanceStruct*)
    chartInstanceVar);
  initialize_c2_hapticsSimBlk_pd((SFc2_hapticsSimBlk_pdInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_hapticsSimBlk_pd(void *chartInstanceVar)
{
  enable_c2_hapticsSimBlk_pd((SFc2_hapticsSimBlk_pdInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_hapticsSimBlk_pd(void *chartInstanceVar)
{
  disable_c2_hapticsSimBlk_pd((SFc2_hapticsSimBlk_pdInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_hapticsSimBlk_pd(void *chartInstanceVar)
{
  sf_c2_hapticsSimBlk_pd((SFc2_hapticsSimBlk_pdInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_hapticsSimBlk_pd(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_hapticsSimBlk_pd
    ((SFc2_hapticsSimBlk_pdInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_hapticsSimBlk_pd();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_hapticsSimBlk_pd(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_hapticsSimBlk_pd();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_hapticsSimBlk_pd((SFc2_hapticsSimBlk_pdInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_hapticsSimBlk_pd(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_hapticsSimBlk_pd(S);
}

static void sf_opaque_set_sim_state_c2_hapticsSimBlk_pd(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_hapticsSimBlk_pd(S, st);
}

static void sf_opaque_terminate_c2_hapticsSimBlk_pd(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_hapticsSimBlk_pdInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_hapticsSimBlk_pd((SFc2_hapticsSimBlk_pdInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_hapticsSimBlk_pd_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_hapticsSimBlk_pd((SFc2_hapticsSimBlk_pdInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_hapticsSimBlk_pd(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_hapticsSimBlk_pd((SFc2_hapticsSimBlk_pdInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_hapticsSimBlk_pd(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_hapticsSimBlk_pd_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,infoStruct,2,4);
    }

    sf_set_rtw_dwork_info(S,infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3723152087U));
  ssSetChecksum1(S,(1092412308U));
  ssSetChecksum2(S,(3042272796U));
  ssSetChecksum3(S,(1514800018U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_hapticsSimBlk_pd(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_hapticsSimBlk_pd(SimStruct *S)
{
  SFc2_hapticsSimBlk_pdInstanceStruct *chartInstance;
  chartInstance = (SFc2_hapticsSimBlk_pdInstanceStruct *)malloc(sizeof
    (SFc2_hapticsSimBlk_pdInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_hapticsSimBlk_pdInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_hapticsSimBlk_pd;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_hapticsSimBlk_pd_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_hapticsSimBlk_pd(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_hapticsSimBlk_pd(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_hapticsSimBlk_pd(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_hapticsSimBlk_pd_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
