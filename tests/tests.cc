#include <gtest/gtest.h>

#include "decimal.h"

using namespace utils::finantial;

TEST(Decimal, ConstructorDefault) {
  EXPECT_EQ(static_cast<std::string>(Decimal()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("5.3")), "+5.3");
  EXPECT_EQ(static_cast<std::string>(Decimal("-5.3")), "-5.3");
  EXPECT_EQ(static_cast<std::string>(Decimal(".5")), "+0.5");
  EXPECT_EQ(static_cast<std::string>(Decimal("-.005")), "-0.005");
  EXPECT_EQ(static_cast<std::string>(Decimal("-.80324809283904824342323423434432424243245")), "-0.80324809283904824342323423434");
}

TEST(Decimal, ConstructorCopy) {
  Decimal a;
  Decimal b (a);
  EXPECT_EQ(static_cast<std::string>(b), "+0");

  Decimal c("-.005");
  Decimal d(c);

  EXPECT_EQ(static_cast<std::string>(d), "-0.005");
}

TEST(Decimal, ConstructorMove) {
  Decimal a;
  Decimal b (std::move(a));
  EXPECT_EQ(static_cast<std::string>(a), "+0");
  EXPECT_EQ(static_cast<std::string>(b), "+0");

  Decimal c("-.005");
  Decimal d(std::move(c));
  EXPECT_EQ(static_cast<std::string>(c), "-0.005");
  EXPECT_EQ(static_cast<std::string>(d), "-0.005");
}

TEST(Decimal, ConstructorInvalidInput) {
  EXPECT_EQ(static_cast<std::string>(Decimal("invalid")), "+0");
}

TEST(Decimal, AssignmentsStringView) {
  std::string_view value = "5.3";
  Decimal a = value;
  EXPECT_EQ(static_cast<std::string>(a), "+5.3");

  value = "-5.3";
  Decimal b = value;
  EXPECT_EQ(static_cast<std::string>(b), "-5.3");
}

TEST(Decimal, AssignmentsCopy) {
  Decimal a("-.00432234234");
  Decimal b(a);
  EXPECT_EQ(static_cast<std::string>(b), "-0.00432234234");
}

TEST(Decimal, AssignmentsMove) {
  Decimal a("-.00432234234");
  Decimal b(std::move(a));
  EXPECT_EQ(static_cast<std::string>(b), "-0.00432234234");
}

TEST(Decimal, AssignmetsInvalidInput) {
  Decimal a = std::string_view("invalid");
  EXPECT_EQ(static_cast<std::string>(a), "+0");
}

TEST(Decimal, CastToString) {
  Decimal a("-.00432234234");
  EXPECT_EQ(static_cast<std::string>(a), "-0.00432234234");
}

TEST(Decimal, ComparisonEqual_0) {
  EXPECT_TRUE(Decimal("2.1234") == Decimal("2.1234"));
}

TEST(Decimal, ComparisonEqual_1) {
  EXPECT_FALSE(Decimal("2.1234") == Decimal("2.1235"));
}

TEST(Decimal, ComparisonEqual_2) {
  EXPECT_TRUE(Decimal("23132217092805717135676") == Decimal("23132217092805717135676"));
}

TEST(Decimal, ComparisonEqual_3) {
  EXPECT_TRUE(Decimal("-23132217092805717135676") == Decimal("-23132217092805717135676"));
}

TEST(Decimal, ComparisonEqual_4) {
  EXPECT_TRUE(Decimal("2") == Decimal("2.00"));
}

TEST(Decimal, ComparisonEqual_5) {
  EXPECT_FALSE(Decimal("2") == Decimal("3"));
}

TEST(Decimal, ComparisonEqual_6) {
  EXPECT_TRUE(Decimal("0.000000000000000000000000000") == Decimal("0"));
}

TEST(Decimal, ComparisonEqual_7) {
  EXPECT_FALSE(Decimal("3") == Decimal("-3"));
}

TEST(Decimal, ComparisonEqual_8) {
  EXPECT_TRUE(Decimal("2.222212") == Decimal("2.222212"));
}

TEST(Decimal, ComparisonEqual_9) {
  EXPECT_TRUE(Decimal("2.22221200000000000") == Decimal("2.222212"));
}

TEST(Decimal, ComparisonEqual_10) {
  EXPECT_FALSE(Decimal("3.2222121") == Decimal("3.222212"));
}

TEST(Decimal, ComparisonEqual_11) {
  EXPECT_FALSE(Decimal("2.222212") == Decimal("-2.222212"));
}

TEST(Decimal, ComparisonEqual_12) {
  EXPECT_FALSE(Decimal("-364748") == Decimal("1"));
}

TEST(Decimal, ComparisonEqual_13) {
  EXPECT_FALSE(Decimal("987456543210.0") == Decimal("98745654321.0"));
}

TEST(Decimal, ComparisonEqual_14) {
  EXPECT_TRUE(Decimal("-9878798789.5867800") == Decimal("-9878798789.58678"));
}

TEST(Decimal, ComparisonEqual_15) {
  EXPECT_FALSE(Decimal("1.0") == Decimal("9999999999999999999"));
}

TEST(Decimal, ComparisonEqual_16) {
  EXPECT_TRUE(Decimal("18446744073709551615") == Decimal("18446744073709551615.000000000"));
}

TEST(Decimal, ComparisonEqual_17) {
  EXPECT_TRUE(Decimal("-545454512454545.35265454545645") == Decimal("-545454512454545.35265454545645"));
}

TEST(Decimal, ComparisonEqual_18) {
  EXPECT_FALSE(Decimal("-545454512454545.35265454545645") == Decimal("-5.352654545456454545645464"));
}

TEST(Decimal, ComparisonEqual_19) {
  EXPECT_FALSE(Decimal("7961327845421.879754123131254") == Decimal("7961327.845421879754123131254"));
}

TEST(Decimal, ComparisonEqual_20) {
  EXPECT_FALSE(Decimal("-87654323456.98765456789876530") == Decimal("-87654323456.98765456789876531"));
}

TEST(Decimal, ComparisonEqual_21) {
  EXPECT_TRUE(Decimal("79228162514264337593543950335") == Decimal("79228162514264337593543950335"));
}

TEST(Decimal, ComparisonEqual_22) {
  EXPECT_FALSE(Decimal("7922816251426433759354395033") == Decimal("-7922816251426433759354395033"));
}

TEST(Decimal, ComparisonEqual_23) {
  EXPECT_TRUE(Decimal("-7.7545545454546589781677545545") == Decimal("-7.7545545454546589781677545545"));
}

TEST(Decimal, ComparisonNotEqual_0) {
  EXPECT_FALSE(Decimal("2") != Decimal("2"));
}

TEST(Decimal, ComparisonNotEqual_1) {
  EXPECT_FALSE(Decimal("0") != Decimal("0.000000000000000000000000000"));
}

TEST(Decimal, ComparisonNotEqual_2) {
  EXPECT_TRUE(Decimal("3.2222121") != Decimal("3.222212"));
}

TEST(Decimal, ComparisonNotEqual_3) {
  EXPECT_TRUE(Decimal("-364748") != Decimal("1"));
}

TEST(Decimal, ComparisonNotEqual_4) {
  EXPECT_TRUE(Decimal("9999999999999999999") != Decimal("1"));
}

TEST(Decimal, ComparisonNotEqual_5) {
  EXPECT_FALSE(Decimal("18446744073709551615") != Decimal("18446744073709551615.000000000"));
}

TEST(Decimal, ComparisonNotEqual_6) {
  EXPECT_TRUE(Decimal("-545454512454545.35265454545645") != Decimal("-5.352654545456454545645464"));
}

TEST(Decimal, ComparisonNotEqual_7) {
  EXPECT_TRUE(Decimal("79228162514264337593543950335") != Decimal("-79228162514264337593543950335"));
}

TEST(Decimal, ComparisonNotEqual_8) {
  EXPECT_TRUE(Decimal("-2.51426433759354") != Decimal("-2.5142643375935430000000000000"));
}

TEST(Decimal, ComparisonLess_0) {
  EXPECT_FALSE(Decimal("2.351") < Decimal("2.351"));
}

TEST(Decimal, ComparisonLess_1) {
  EXPECT_FALSE(Decimal("2.351") < Decimal("-2.351"));
}

TEST(Decimal, ComparisonLess_2) {
  EXPECT_FALSE(Decimal("-2.351") < Decimal("-2.351"));
}

TEST(Decimal, ComparisonLess_3) {
  EXPECT_TRUE(Decimal("-2.351") < Decimal("2.351"));
}

TEST(Decimal, ComparisonLess_4) {
  EXPECT_FALSE(Decimal("2.22221200000001000") < Decimal("2.222212"));
}

TEST(Decimal, ComparisonLess_5) {
  EXPECT_FALSE(Decimal("-9878798789.5867800") < Decimal("-9878798789.58678"));
}

TEST(Decimal, ComparisonLess_6) {
  EXPECT_TRUE(Decimal("-545454512454545.35265454545645") < Decimal("-5.352654545456454545645464"));
}

TEST(Decimal, ComparisonLess_7) {
  EXPECT_FALSE(Decimal("79228162514264337593543950335") < Decimal("79228162514264337593543950335"));
}

TEST(Decimal, ComparisonLessOrEqual_0) {
  EXPECT_TRUE(Decimal("2.351") <= Decimal("2.351"));
}

TEST(Decimal, ComparisonLessOrEqual_1) {
  EXPECT_FALSE(Decimal("2.351") <= Decimal("-2.351"));
}

TEST(Decimal, ComparisonLessOrEqual_2) {
  EXPECT_TRUE(Decimal("-2.351") <= Decimal("-2.351"));
}

TEST(Decimal, ComparisonLessOrEqual_3) {
  EXPECT_TRUE(Decimal("0") <= Decimal("0.000000000000000000000000000"));
}

TEST(Decimal, ComparisonLessOrEqual_4) {
  EXPECT_TRUE(Decimal("0.000000000000000000000000000") <= Decimal("0"));
}

TEST(Decimal, ComparisonLessOrEqual_5) {
  EXPECT_TRUE(Decimal("-3") <= Decimal("3"));
}

TEST(Decimal, ComparisonLessOrEqual_6) {
  EXPECT_TRUE(Decimal("-545454512454545.35265454545645") <= Decimal("-5.352654545456454545645464"));
}

TEST(Decimal, ComparisonLessOrEqual_7) {
  EXPECT_TRUE(Decimal("79228162514264337593543950335") <= Decimal("79228162514264337593543950335"));
}

TEST(Decimal, ComparisonLessOrEqual_8) {
  EXPECT_TRUE(Decimal("2.51426433759354") <= Decimal("2.5142643375935430000000000000"));
}

TEST(Decimal, ComparisonLessOrEqual_9) {
  EXPECT_FALSE(Decimal("0.000000000000000000000000001") <= Decimal("0"));
}

TEST(Decimal, ComparisonLessOrEqual_10) {
  EXPECT_TRUE(Decimal("-545454512454545.35265454545645") <= Decimal("-545454512454545.35265454545645"));
}

TEST(Decimal, ComparisonLessOrEqual_11) {
  EXPECT_TRUE(Decimal("-545454512454545.35265454545645") <= Decimal("-5.352654545456454545645464"));
}

TEST(Decimal, ComparisonLessOrEqual_12) {
  EXPECT_TRUE(Decimal("79228162514264337593543950335") <= Decimal("79228162514264337593543950335"));
}

TEST(Decimal, ComparisonLessOrEqual_13) {
  EXPECT_TRUE(Decimal("-79228162514264337593543950335") <= Decimal("79228162514264337593543950335"));
}

TEST(Decimal, ComparisonLessOrEqual_14) {
  EXPECT_FALSE(Decimal("79228162514264337593543950335") <= Decimal("-79228162514264337593543950335"));
}

TEST(Decimal, ComparisonGreater_0) {
  EXPECT_FALSE(Decimal("2.351") > Decimal("2.351"));
}

TEST(Decimal, ComparisonGreater_1) {
  EXPECT_TRUE(Decimal("2.351") > Decimal("-2.351"));
}

TEST(Decimal, ComparisonGreater_2) {
  EXPECT_FALSE(Decimal("-2.351") > Decimal("-2.351"));
}

TEST(Decimal, ComparisonGreater_3) {
  EXPECT_FALSE(Decimal("-0") > Decimal("0"));
}

TEST(Decimal, ComparisonGreater_4) {
  EXPECT_FALSE(Decimal("0") > Decimal("-0"));
}

TEST(Decimal, ComparisonGreater_5) {
  EXPECT_FALSE(Decimal("3.0000000000000000000000000000000000000000000000001") > Decimal("3"));
}

TEST(Decimal, ComparisonGreater_6) {
  EXPECT_FALSE(Decimal("79228162514264337593543950335") > Decimal("79228162514264337593543950335"));
}

TEST(Decimal, ComparisonGreater_7) {
  EXPECT_TRUE(Decimal("7922816251426433759354395033.5") > Decimal("7922816251426433759354395033.4"));
}

TEST(Decimal, ComparisonGreaterOrEqual_0) {
  EXPECT_TRUE(Decimal("2.351") >= Decimal("2.351"));
}

TEST(Decimal, ComparisonGreaterOrEqual_1) {
  EXPECT_TRUE(Decimal("2.351") >= Decimal("-2.351"));
}

TEST(Decimal, ComparisonGreaterOrEqual_2) {
  EXPECT_TRUE(Decimal("2.3510000000000030000000000000") >= Decimal("2.35100000000000000000000004"));
}

TEST(Decimal, OperatorUnaryMinus_0) {
  EXPECT_TRUE(-Decimal("-2.1234") == Decimal("2.1234"));
}

TEST(Decimal, OperatorUnaryMinus_1) {
  EXPECT_TRUE(-Decimal("0.000000000000000000000000000") == Decimal("0.000000000000000000000000000"));
}

TEST(Decimal, OperatorUnaryMinus_2) {
  EXPECT_TRUE(-Decimal("2.22221200000001000") == Decimal("-2.22221200000001000"));
}

TEST(Decimal, OperatorUnaryMinus_3) {
  EXPECT_TRUE(-Decimal("18446744073709551615") == Decimal("-18446744073709551615"));
}

TEST(Decimal, OperatorUnaryMinus_4) {
  EXPECT_TRUE(-Decimal("-796214545.3526545454564545456") == Decimal("796214545.3526545454564545456"));
}

TEST(Decimal, OperatorUnaryMinus_5) {
  EXPECT_EQ(-Decimal("0") , Decimal("0"));
}

TEST(Decimal, OperatorUnaryMinus_6) {
  EXPECT_EQ(-Decimal("79228162514264337593543950335"), Decimal("-79228162514264337593543950335"));
}

TEST(Decimal, OperatorAdd_0) {
  EXPECT_EQ(Decimal("2.351") + Decimal("-2.351"), Decimal("0"));
}

TEST(Decimal, OperatorAdd_1) {
  EXPECT_EQ(Decimal("2.351") + Decimal("2.351"), Decimal("4.702"));
}

TEST(Decimal, OperatorAdd_2) {
  EXPECT_EQ(Decimal("2") + Decimal("3"), Decimal("5"));
}

TEST(Decimal, OperatorAdd_3) {
  EXPECT_EQ(Decimal("0") + Decimal("3"), Decimal("3"));
}

TEST(Decimal, OperatorAdd_4) {
  EXPECT_EQ(Decimal("2") + Decimal("0"), Decimal("2"));
}

TEST(Decimal, OperatorAddAndAssign_0) {
  EXPECT_EQ(Decimal("2") += Decimal("0"), Decimal("2"));
}

TEST(Decimal, OperatorAddAndAssign_1) {
  EXPECT_EQ(Decimal("65658654") += Decimal("2"), Decimal("65658656"));
}

TEST(Decimal, OperatorAddAndAssign_2) {
  Decimal a("0.0000000");
  Decimal b("2.5");
  for (std::size_t i{}; i < 100000; ++i) {
    a += b;
  }
  EXPECT_EQ(a, Decimal("250000"));
}

TEST(Decimal, OperatorAddAndAssign_3) {
  EXPECT_EQ(Decimal("18446744073709551615.0") += Decimal("965453154"), Decimal("18446744074675004769.0"));
}

TEST(Decimal, OperatorAddAndAssign_4) {
  Decimal a = Decimal("-545454512454545.35265454545645") += Decimal("-5.352654545456454545645464");
  EXPECT_EQ(static_cast<std::string>(a), "-545454512454550.70530909091290");
}

TEST(Decimal, OperatorAddAndAssign_5) {
  Decimal a = Decimal("7961327845421.879754123131254") += Decimal("0");
  EXPECT_EQ(static_cast<std::string>(a), "+7961327845421.879754123131254");
}

TEST(Decimal, OperatorAddAndAssign_6) {
  Decimal a = Decimal("12345677.987654345678987654346") += Decimal("87654323456.9876545678987653");
  EXPECT_EQ(static_cast<std::string>(a), "+87666669134.97530891357775295");
}

TEST(Decimal, OperatorAddAndAssign_7) {
  Decimal a = Decimal("-12345677.987654345678987654346") += Decimal("87654323456.9876545678987653");
  EXPECT_EQ(static_cast<std::string>(a), "+87641977779.00000022221977764");
}

TEST(Decimal, OperatorAddAndAssign_8) {
  Decimal a = Decimal("-12345677.987654345678987654346") += Decimal("-87654323456.9876545678987653");
  EXPECT_EQ(static_cast<std::string>(a), "-87666669134.97530891357775295");
}

TEST(Decimal, OperatorAddAndAssign_9) {
  Decimal a = Decimal("79228162514264337593543950335") += Decimal("-1");
  EXPECT_EQ(static_cast<std::string>(a), "+79228162514264337593543950334");
}

TEST(Decimal, OperatorAddAndAssign_10) {
  Decimal a = Decimal("2.7986531268974139743") += Decimal("9.979623121254565121244554");
  EXPECT_EQ(static_cast<std::string>(a), "+12.778276248151979095544554");
}

TEST(Decimal, OperatorAddAndAssign_11) {
  Decimal a = Decimal("-0.77545545454546589781") += Decimal("87894515154546456456");
  EXPECT_EQ(static_cast<std::string>(a), "+87894515154546456455.22454454");
}

TEST(Decimal, OperatorAddAndAssign_12) {
  Decimal a = Decimal("79228162514264337593543950335") += Decimal("1");
  EXPECT_EQ(static_cast<std::string>(a), "+79228162514264337593543950336");
}

TEST(Decimal, OperatorAddAndAssign_13) {
  Decimal a = Decimal("-79228162514264337593543950335") += Decimal("-1");
  EXPECT_EQ(static_cast<std::string>(a), "-79228162514264337593543950336");
}

TEST(Decimal, OperatorAddAndAssign_14) {
  Decimal a = Decimal("-79228162514264337593543950335") += Decimal("+79228162514264337593543950335");
  EXPECT_EQ(static_cast<std::string>(a), "+0");
}

TEST(Decimal, OperatorSub_0) {
  Decimal a = Decimal("5") - Decimal("3");
  EXPECT_EQ(static_cast<std::string>(a), "+2");
}

TEST(Decimal, OperatorSub_1) {
  Decimal a = Decimal("3") - Decimal("6");
  EXPECT_EQ(static_cast<std::string>(a), "-3");
}

TEST(Decimal, OperatorSub_2) {
  Decimal a = Decimal("0") - Decimal("8");
  EXPECT_EQ(static_cast<std::string>(a), "-8");
}

TEST(Decimal, OperatorSub_3) {
  Decimal a = Decimal("787891") - Decimal("238471");
  EXPECT_EQ(static_cast<std::string>(a), "+549420");
}

TEST(Decimal, OperatorSub_4) {
  Decimal a = Decimal("9") - Decimal("18571145");
  EXPECT_EQ(static_cast<std::string>(a), "-18571136");
}

TEST(Decimal, OperatorSubAndAssign_0) {
  Decimal a = Decimal("-3187878") -= Decimal("1");
  EXPECT_EQ(static_cast<std::string>(a), "-3187879");
}

TEST(Decimal, OperatorSubAndAssign_1) {
  Decimal a = Decimal("1") -= Decimal("18768768");
  EXPECT_EQ(static_cast<std::string>(a), "-18768767");
}

TEST(Decimal, OperatorSubAndAssign_2) {
  Decimal a = Decimal("-2168564564") -= Decimal("-9");
  EXPECT_EQ(static_cast<std::string>(a), "-2168564555");
}

TEST(Decimal, OperatorSubAndAssign_3) {
  Decimal a = Decimal("9999999999999999999") -= Decimal("1");
  EXPECT_EQ(static_cast<std::string>(a), "+9999999999999999998");
}

TEST(Decimal, OperatorSubAndAssign_4) {
  Decimal a = Decimal("-54896651557845.352654545456455") -= Decimal("21465");
  EXPECT_EQ(static_cast<std::string>(a), "-54896651579310.352654545456455");
}

TEST(Decimal, OperatorSubAndAssign_5) {
  Decimal a = Decimal("-12345677.987654345678987654346") -= Decimal("87654323456.9876545678987653");
  EXPECT_EQ(static_cast<std::string>(a), "-87666669134.97530891357775295");
}

TEST(Decimal, OperatorSubAndAssign_6) {
  Decimal a = Decimal("79228162514264337593543950335") -= Decimal("1");
  EXPECT_EQ(static_cast<std::string>(a), "+79228162514264337593543950334");
}

TEST(Decimal, OperatorSubAndAssign_7) {
  Decimal a = Decimal("0.5456465465486476846545465485") -= Decimal("0.68985125146545154");
  EXPECT_EQ(static_cast<std::string>(a), "-0.1442047049168038553454534515");
}

TEST(Decimal, OperatorSubAndAssign_8) {
  Decimal a = Decimal("-0.77545545454546589781") -= Decimal("87894515154546456456");
  EXPECT_EQ(static_cast<std::string>(a), "-87894515154546456456.77545545");
}

TEST(Decimal, OperatorSubAndAssign_9) {
  Decimal a = Decimal("-1") -= Decimal("-79228162514264337593543950335");
  EXPECT_EQ(static_cast<std::string>(a), "+79228162514264337593543950334");
}

TEST(Decimal, OperatorSubAndAssign_10) {
  Decimal a = Decimal("59978456487987764548465456454") -= Decimal("-48786756456875658915646545165");
  EXPECT_EQ(static_cast<std::string>(a), "+108765212944863423464112001619");
}

TEST(Decimal, OperatorSubAndAssign_11) {
  Decimal a = Decimal("79228162514264337593543950335") -= Decimal("79228162514264337593543950335");
  EXPECT_EQ(static_cast<std::string>(a), "+0");
}

TEST(Decimal, OperatorMul_0) {
  Decimal a = Decimal("2") * Decimal("3");
  EXPECT_EQ(static_cast<std::string>(a), "+6");
}

TEST(Decimal, OperatorMul_1) {
  Decimal a = Decimal("0") * Decimal("3");
  EXPECT_EQ(static_cast<std::string>(a), "+0");
}

TEST(Decimal, OperatorMul_2) {
  Decimal a = Decimal("0.0") * Decimal("3");
  EXPECT_EQ(static_cast<std::string>(a), "+0.0");
}

TEST(Decimal, OperatorMul_3) {
  Decimal a = Decimal("6521") * Decimal("74121");
  EXPECT_EQ(static_cast<std::string>(a), "+483343041");
}

TEST(Decimal, OperatorMulAndAssign_0) {
  Decimal a = Decimal("65658654") * Decimal("5");
  EXPECT_EQ(static_cast<std::string>(a), "+328293270");
}

TEST(Decimal, OperatorMulAndAssign_1) {
  Decimal a = Decimal("1") *= Decimal("98745654321");
  EXPECT_EQ(static_cast<std::string>(a), "+98745654321");
}

TEST(Decimal, OperatorMulAndAssign_2) {
  Decimal a = Decimal("-9878798789") *= Decimal("-3");
  EXPECT_EQ(static_cast<std::string>(a), "+29636396367");
}

TEST(Decimal, OperatorMulAndAssign_3) {
  Decimal a = Decimal("-545454512454545.35265454545645") *= Decimal("54564654");
  EXPECT_EQ(static_cast<std::string>(a), "-29762536744820957894903.254358");
}

TEST(Decimal, OperatorMulAndAssign_4) {
  Decimal a = Decimal("-545454512454545.35265454545645") *= Decimal("-5.352654545456454545645464");
  EXPECT_EQ(static_cast<std::string>(a), "+2919629575429556.4794476881359");
}

TEST(Decimal, OperatorMulAndAssign_5) {
  Decimal a = Decimal("79228162514264337593543950335") *= Decimal("-1");
  EXPECT_EQ(static_cast<std::string>(a), "-79228162514264337593543950335");
}

TEST(Decimal, OperatorMulAndAssign_6) {
  Decimal a = Decimal("18446744073709551617.0") *= Decimal("87654531534564545456464.98565");
  EXPECT_EQ(static_cast<std::string>(a), "+1616940710119015538122712318190672286121839");
}

TEST(Decimal, OperatorMulAndAssign_7) {
  Decimal a = Decimal("79228162514264337593543950335") *= Decimal("-79228162514264337593543950335");
  EXPECT_EQ(static_cast<std::string>(a), "-6277101735386680763835789423049210091073826769276946612225");
}

TEST(Decimal, OperatorMulAndAssign_8) {
  Decimal a = Decimal("0.0000000000000000000000001567") *= Decimal("0.000800090769");
  EXPECT_EQ(static_cast<std::string>(a), "+0.0000000000000000000000000001");
}

TEST(Decimal, OperatorDiv_0) {
  Decimal a = Decimal("30064771176") / Decimal("3");
  EXPECT_EQ(static_cast<std::string>(a), "+10021590392");
}

TEST(Decimal, OperatorDiv_1) {
  Decimal a = Decimal("32768") / Decimal("-2");
  EXPECT_EQ(static_cast<std::string>(a), "-16384");
}

TEST(Decimal, OperatorDiv_2) {
  Decimal a = Decimal("-30064771176") / Decimal("2");
  EXPECT_EQ(static_cast<std::string>(a), "-15032385588");
}

TEST(Decimal, OperatorDiv_3) {
  Decimal a = Decimal("30064771176") / Decimal("-2");
  EXPECT_EQ(static_cast<std::string>(a), "-15032385588");
}

TEST(Decimal, OperatorDiv_4) {
  Decimal a = Decimal("0") / Decimal("0.015");
  EXPECT_EQ(static_cast<std::string>(a), "+0");
}

TEST(Decimal, OperatorDivAndAssign_0) {
  Decimal a = Decimal("-101") /= Decimal("10.1");
  EXPECT_EQ(static_cast<std::string>(a), "-10");
}

TEST(Decimal, OperatorDivAndAssign_1) {
  Decimal a = Decimal("-101") /= Decimal("0.0");
  EXPECT_EQ(static_cast<std::string>(a), "+0");
}

TEST(Decimal, OperatorDivAndAssign_2) {
  Decimal a = Decimal("3") /= Decimal("2");
  EXPECT_EQ(static_cast<std::string>(a), "+1.5");
}

TEST(Decimal, OperatorDivAndAssign_3) {
  Decimal a = Decimal("2") /= Decimal("3");
  EXPECT_EQ(static_cast<std::string>(a), "+0.6666666666666666666666666667");
}

TEST(Decimal, OperatorDivAndAssign_4) {
  Decimal a = Decimal("9432747237234.43278947893292387944") /= Decimal("-0.0000000000004324234324234322");
  EXPECT_EQ(static_cast<std::string>(a), "-21813681983814922954896245.549");
}


TEST(Decimal, OperatorMod_0) {
  Decimal a = Decimal("2.54") % Decimal("3.21");
  EXPECT_EQ(static_cast<std::string>(a), "+2.54");
}

TEST(Decimal, OperatorMod_1) {
  Decimal a = Decimal("3.42") % Decimal("3.21");
  EXPECT_EQ(static_cast<std::string>(a), "+0.21");
}

TEST(Decimal, OperatorMod_2) {
  Decimal a = Decimal("-98765") % Decimal("1234");
  EXPECT_EQ(static_cast<std::string>(a), "-45");
}

TEST(Decimal, OperatorMod_3) {
  Decimal a = Decimal("30198") % Decimal("20210");
  EXPECT_EQ(static_cast<std::string>(a), "+9988");
}

TEST(Decimal, OperatorMod_4) {
  Decimal a = Decimal("9432747237234.43278947893292387944") % Decimal("0.0000000000004324234324234322");
  EXPECT_EQ(static_cast<std::string>(a), "+0.0000000000002373649422079110");
}

TEST(Decimal, OperatorMod_5) {
  Decimal a = Decimal("21") % Decimal("0.0");
  EXPECT_EQ(static_cast<std::string>(a), "+0.0");
}

TEST(Decimal, OperatorMod_6) {
  Decimal a = Decimal("5") % Decimal("5.0");
  EXPECT_EQ(static_cast<std::string>(a), "+0.0");
}

TEST(Decimal, OperatorMod_7) {
  Decimal a = Decimal("3.5") % Decimal("3.0");
  EXPECT_EQ(static_cast<std::string>(a), "+0.5");
}

TEST(Decimal, OperatorModAndAssign_0) {
  Decimal a = Decimal("3.5") %= Decimal("3.0");
  EXPECT_EQ(static_cast<std::string>(a), "+0.5");
}

TEST(Decimal, OperatorModAndAssign_1) {
  Decimal a = Decimal("-2.4363463") %= Decimal("2.0");
  EXPECT_EQ(static_cast<std::string>(a), "-0.4363463");
}

TEST(Decimal, Trancate_0) {
  EXPECT_EQ(static_cast<std::string>(Decimal("2.1234").trunc()), "+2");
  EXPECT_EQ(static_cast<std::string>(Decimal("457.000001").trunc()), "+457");
  EXPECT_EQ(static_cast<std::string>(Decimal("0.000000000000000000000000000").trunc()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("79228162514264337593543950335").trunc()), "+79228162514264337593543950335");
}

TEST(Decimal, Trancate_1) {
  EXPECT_EQ(static_cast<std::string>(Decimal("-2.1234").trunc()), "-2");
  EXPECT_EQ(static_cast<std::string>(Decimal("-457.000001").trunc()), "-457");
  EXPECT_EQ(static_cast<std::string>(Decimal("-0.000000000000000000000000000").trunc()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("-79228162514264337593543950335").trunc()), "-79228162514264337593543950335");
}

TEST(Decimal, Round_0) {
  EXPECT_EQ(static_cast<std::string>(Decimal("0.0").round()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("652.34631").round()), "+652");
  EXPECT_EQ(static_cast<std::string>(Decimal("4.97623323").round()), "+5");
  EXPECT_EQ(static_cast<std::string>(Decimal("4.5").round()), "+5");
  EXPECT_EQ(static_cast<std::string>(Decimal("4.0").round()), "+4");
}

TEST(Decimal, Round_1) {
  EXPECT_EQ(static_cast<std::string>(Decimal("-0.0").round()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("-2.4363463").round()), "-2");
  EXPECT_EQ(static_cast<std::string>(Decimal("-0.45").round()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("-4.5").round()), "-5");
  EXPECT_EQ(static_cast<std::string>(Decimal("-4.99").round()), "-5");
  EXPECT_EQ(static_cast<std::string>(Decimal("-4.0").round()), "-4");
}

TEST(Decimal, Floor_0) {
  EXPECT_EQ(static_cast<std::string>(Decimal("0.0").floor()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("652.34631").floor()), "+652");
  EXPECT_EQ(static_cast<std::string>(Decimal("4.97623323").floor()), "+4");
  EXPECT_EQ(static_cast<std::string>(Decimal("4.5").floor()), "+4");
  EXPECT_EQ(static_cast<std::string>(Decimal("4").floor()), "+4");
}

TEST(Decimal, Floor_1) {
  EXPECT_EQ(static_cast<std::string>(Decimal("-0.0").floor()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("-2.4363463").floor()), "-3");
  EXPECT_EQ(static_cast<std::string>(Decimal("-0.45").floor()), "-1");
  EXPECT_EQ(static_cast<std::string>(Decimal("-4.5").floor()), "-5");
  EXPECT_EQ(static_cast<std::string>(Decimal("-4.99").floor()), "-5");
  EXPECT_EQ(static_cast<std::string>(Decimal("-4.0").floor()), "-4");
}

TEST(Decimal, Ceil_0) {
  EXPECT_EQ(static_cast<std::string>(Decimal("0.0").ceil()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("652.34631").ceil()), "+653");
  EXPECT_EQ(static_cast<std::string>(Decimal("4.97623323").ceil()), "+5");
  EXPECT_EQ(static_cast<std::string>(Decimal("4.5").ceil()), "+5");
  EXPECT_EQ(static_cast<std::string>(Decimal("4").ceil()), "+4");
  EXPECT_EQ(static_cast<std::string>(Decimal("4.000000001").ceil()), "+5");
}

TEST(Decimal, Ceil_1) {
  EXPECT_EQ(static_cast<std::string>(Decimal("-0.0").ceil()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("-2.4363463").ceil()), "-2");
  EXPECT_EQ(static_cast<std::string>(Decimal("-0.45").ceil()), "+0");
  EXPECT_EQ(static_cast<std::string>(Decimal("-4.5").ceil()), "-4");
  EXPECT_EQ(static_cast<std::string>(Decimal("-4.99").ceil()), "-4");
  EXPECT_EQ(static_cast<std::string>(Decimal("-4.0").ceil()), "-4");
}
