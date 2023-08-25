#include <gtest/gtest.h>

#include "../s21_SmartCalc_v2/model/s21_graph.h"

struct answer_tests {
  std::vector<double> sin_X = {-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10};
  std::vector<double> sin_Y = {0.54402111088, -0.98935824662, 0.27941549819,
                               0.7568024953,  -0.90929742682, 0.0,
                               0.90929742682, -0.7568024953,  -0.27941549819,
                               0.98935824662, -0.54402111088};

  std::vector<double> linear_X = {-999999,   -799999.2, -599999.4,
                                  -399999.6, -199999.8, 5.8207660913467407e-11,
                                  199999.8,  399999.6,  599999.4,
                                  799999.2,  999999};
  std::vector<double> linear_Y = {
      -1999993, -1599993.4, -1199993.8, -799994.2, -399994.6, 5.00000000012,
      400004.6, 800004.2,   1200003.8,  1600003.4, 2000003};

  std::vector<double> ln_X = {1,   1.9, 2.8, 3.7, 4.6, 5.5,
                              6.4, 7.3, 8.2, 9.1, 10};
  std::vector<double> ln_Y = {0,
                              0.64185388617,
                              1.02961941718,
                              1.30833281965,
                              1.5260563035,
                              1.70474809224,
                              1.85629799037,
                              1.98787434815,
                              2.10413415427,
                              2.20827441352,
                              2.30258509299};
};

TEST(graph_test, sin_test) {
  answer_tests sin;
  s21::graph expression;
  s21::data_graph input_values = {"sin(x)", -10, 10, -10, 10, 10};
  expression.set_data_graph(input_values);
  s21::result_graph result = expression.get_result();
  for (auto it_x = result.X.begin(), it_y = result.Y.begin(),
            it_tx = sin.sin_X.begin(), it_ty = sin.sin_Y.begin();
       it_x != result.X.end(); ++it_x, ++it_y, ++it_tx, ++it_ty) {
    EXPECT_DOUBLE_EQ(*it_x, *it_tx);
    EXPECT_NEAR(*it_y, *it_ty, 1e-7);
  }
  EXPECT_TRUE(result.status);
}

TEST(graph_test, linear_test) {
  answer_tests linear;
  s21::graph expression;
  s21::data_graph input_values = {"2x+5", -999999, 999999, -999999, 999999, 10};
  expression.set_data_graph(input_values);
  s21::result_graph result = expression.get_result();
  for (auto it_x = result.X.begin(), it_y = result.Y.begin(),
            it_tx = linear.linear_X.begin(), it_ty = linear.linear_Y.begin();
       it_x != result.X.end(); ++it_x, ++it_y, ++it_tx, ++it_ty) {
    EXPECT_DOUBLE_EQ(*it_x, *it_tx);
    EXPECT_NEAR(*it_y, *it_ty, 1e-7);
  }
  EXPECT_TRUE(result.status);
}

TEST(graph_test, ln_test) {
  answer_tests ln;
  s21::graph expression;
  s21::data_graph input_values = {"lnx", 1, 10, -1, 10, 10};
  expression.set_data_graph(input_values);
  s21::result_graph result = expression.get_result();
  for (auto it_x = result.X.begin(), it_y = result.Y.begin(),
            it_tx = ln.ln_X.begin(), it_ty = ln.ln_Y.begin();
       it_x != result.X.end(); ++it_x, ++it_y, ++it_tx, ++it_ty) {
    EXPECT_DOUBLE_EQ(*it_x, *it_tx);
    EXPECT_NEAR(*it_y, *it_ty, 1e-7);
  }
  EXPECT_TRUE(result.status);
}

TEST(graph_test, false_test) {
  answer_tests ln;
  s21::graph expression;
  s21::data_graph input_values = {"x^2", -10000000, 10000000, -10, 10, 10};
  expression.set_data_graph(input_values);
  s21::result_graph result = expression.get_result();
  EXPECT_FALSE(result.status);
}

TEST(graph_test, false_test_1) {
  answer_tests ln;
  s21::graph expression;
  s21::data_graph input_values = {"x^2", -10, 10, -10000000, 10000000, 10};
  expression.set_data_graph(input_values);
  s21::result_graph result = expression.get_result();
  EXPECT_FALSE(result.status);
}

TEST(graph_test, false_test_2) {
  answer_tests ln;
  s21::graph expression;
  s21::data_graph input_values = {"x^2", -10, 10, 10, -10, 10};
  expression.set_data_graph(input_values);
  s21::result_graph result = expression.get_result();
  EXPECT_FALSE(result.status);
}

TEST(graph_test, false_test_3) {
  answer_tests ln;
  s21::graph expression;
  s21::data_graph input_values = {"x^2", 10, -10, 10, -10, 10};
  expression.set_data_graph(input_values);
  s21::result_graph result = expression.get_result();
  EXPECT_FALSE(result.status);
}
