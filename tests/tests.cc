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
  EXPECT_EQ(static_cast<std::string>(a), "+0.0000000000000000000000000001253742235023");
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
  EXPECT_EQ(static_cast<std::string>(a), "+0.6666666666666666666666666666");
}

TEST(Decimal, OperatorDivAndAssign_4) {
  Decimal a = Decimal("9432747237234.43278947893292387944") /= Decimal("-0.0000000000004324234324234322");
  EXPECT_EQ(static_cast<std::string>(a), "-21813681983814922954896245.548");
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







// START_TEST(castom_round_4) {
//   castom_decimal src, origin, result;
//   // src = -2.4363463;
//   src.bits[0] = 0b00000001011100111100000111000111;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000001110000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = -2;
//   origin.bits[0] = 0b00000000000000000000000000000010;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_5) {
//   castom_decimal src, origin, result;
//   // src = -0.0;
//   src.bits[0] = 0b00000000000000000000000000000000;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000010000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 0;
//   origin.bits[0] = 0b00000000000000000000000000000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_6) {
//   castom_decimal src, origin, result;
//   // src = -0.45;
//   src.bits[0] = 0b00000000000000000000000000101101;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000100000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 0;
//   origin.bits[0] = 0b00000000000000000000000000000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_7) {
//   castom_decimal src, origin, result;
//   // src = 652.34631;
//   src.bits[0] = 0b00000011111000110110011011000111;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000001010000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 652;
//   origin.bits[0] = 0b00000000000000000000001010001100;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_8) {
//   castom_decimal src, origin, result;
//   // src = 4.97623323;
//   src.bits[0] = 0b00011101101010010010000100011011;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000010000000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 5;
//   origin.bits[0] = 0b00000000000000000000000000000101;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_9) {
//   castom_decimal src, origin, result;
//   // src = 65658654.59;
//   src.bits[0] = 0b10000111010110110010011111110011;
//   src.bits[1] = 0b00000000000000000000000000000001;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000100000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 65658655;
//   origin.bits[0] = 0b00000011111010011101111100011111;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_10) {
//   castom_decimal src, origin, result;
//   // src = -364748.110;
//   src.bits[0] = 0b00010101101111011001110101001110;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000110000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = -364748;
//   origin.bits[0] = 0b00000000000001011001000011001100;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_11) {
//   castom_decimal src, origin, result;
//   // src = 1.9874565432111;
//   src.bits[0] = 0b01101000011010011010001100101111;
//   src.bits[1] = 0b00000000000000000001001000010011;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000011010000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 2;
//   origin.bits[0] = 0b00000000000000000000000000000010;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_12) {
//   castom_decimal src, origin, result;
//   // src = -98.78798789312;
//   src.bits[0] = 0b00010110010010101110101011000000;
//   src.bits[1] = 0b00000000000000000000100011111100;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000010110000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = -99;
//   origin.bits[0] = 0b00000000000000000000000001100011;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_13) {
//   castom_decimal src, origin, result;
//   // src = 999999999999999999911.3;
//   src.bits[0] = 0b10110010001111111111110010001001;
//   src.bits[1] = 0b00011001111000001100100110111010;
//   src.bits[2] = 0b00000000000000000000001000011110;
//   src.bits[3] = 0b00000000000000010000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 999999999999999999911;
//   origin.bits[0] = 0b11011110100111111111111110100111;
//   origin.bits[1] = 0b00110101110010011010110111000101;
//   origin.bits[2] = 0b00000000000000000000000000110110;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_14) {
//   castom_decimal src, origin, result;
//   // src = -545454512454545.35265454545645;
//   src.bits[0] = 0b10000010111000100101101011101101;
//   src.bits[1] = 0b11111001111010000010010110101101;
//   src.bits[2] = 0b10110000001111101111000010010100;
//   src.bits[3] = 0b10000000000011100000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = -545454512454545;
//   origin.bits[0] = 0b10000110011101001011101110010001;
//   origin.bits[1] = 0b00000000000000011111000000010110;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_15) {
//   castom_decimal src, origin, result;
//   // src = 545454512454545.35265454545645;
//   src.bits[0] = 0b10000010111000100101101011101101;
//   src.bits[1] = 0b11111001111010000010010110101101;
//   src.bits[2] = 0b10110000001111101111000010010100;
//   src.bits[3] = 0b00000000000011100000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 545454512454545;
//   origin.bits[0] = 0b10000110011101001011101110010001;
//   origin.bits[1] = 0b00000000000000011111000000010110;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_16) {
//   castom_decimal src, origin, result;
//   // src = 7961327845421.879754123131254;
//   src.bits[0] = 0b01001110111001000011100101110110;
//   src.bits[1] = 0b01001011001101011010000111011001;
//   src.bits[2] = 0b00011001101110010111010010111111;
//   src.bits[3] = 0b00000000000011110000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 7961327845422;
//   origin.bits[0] = 0b10100100000111100100000000101110;
//   origin.bits[1] = 0b00000000000000000000011100111101;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_17) {
//   castom_decimal src, origin, result;
//   // src = 12345677.987654345678987654346;
//   src.bits[0] = 0b10010001000010101111010011001010;
//   src.bits[1] = 0b11000000010001011101010111110010;
//   src.bits[2] = 0b00100111111001000001101100000000;
//   src.bits[3] = 0b00000000000101010000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 12345678;
//   origin.bits[0] = 0b00000000101111000110000101001110;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_18) {
//   castom_decimal src, origin, result;
//   // src = -12345677.987654345678987654346;
//   src.bits[0] = 0b10010001000010101111010011001010;
//   src.bits[1] = 0b11000000010001011101010111110010;
//   src.bits[2] = 0b00100111111001000001101100000000;
//   src.bits[3] = 0b10000000000101010000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = -12345678;
//   origin.bits[0] = 0b00000000101111000110000101001110;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_19) {
//   castom_decimal src, origin, result;
//   // src = 87654323456.9876545678987653;
//   src.bits[0] = 0b00010001110011011101000110000101;
//   src.bits[1] = 0b11110101101111000110111111000000;
//   src.bits[2] = 0b00000010110101010000111100111111;
//   src.bits[3] = 0b00000000000100000000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 87654323457;
//   origin.bits[0] = 0b01101000100110101101010100000001;
//   origin.bits[1] = 0b00000000000000000000000000010100;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_20) {
//   castom_decimal src, origin, result;
//   // src = 336565445454313.859865545;
//   src.bits[0] = 0b00111110111111000101101111001001;
//   src.bits[1] = 0b00111111110101011110000010001011;
//   src.bits[2] = 0b00000000000000000100011101000101;
//   src.bits[3] = 0b00000000000010010000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 336565445454314;
//   origin.bits[0] = 0b10111111110100011110100111101010;
//   origin.bits[1] = 0b00000000000000010011001000011010;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_21) {
//   castom_decimal src, origin, result;
//   // src = -15456451234534;
//   src.bits[0] = 0b10111100010010010000101011100110;
//   src.bits[1] = 0b00000000000000000000111000001110;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000000000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = -15456451234534;
//   origin.bits[0] = 0b10111100010010010000101011100110;
//   origin.bits[1] = 0b00000000000000000000111000001110;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_22) {
//   castom_decimal src, origin, result;
//   // src = -0.42354543545;
//   src.bits[0] = 0b11011100100001110000101110111001;
//   src.bits[1] = 0b00000000000000000000000000001001;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000010110000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 0;
//   origin.bits[0] = 0b00000000000000000000000000000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_23) {
//   castom_decimal src, origin, result;
//   // src = 79228162514264337593543950335;
//   src.bits[0] = 0b11111111111111111111111111111111;
//   src.bits[1] = 0b11111111111111111111111111111111;
//   src.bits[2] = 0b11111111111111111111111111111111;
//   src.bits[3] = 0b00000000000000000000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 79228162514264337593543950335;
//   origin.bits[0] = 0b11111111111111111111111111111111;
//   origin.bits[1] = 0b11111111111111111111111111111111;
//   origin.bits[2] = 0b11111111111111111111111111111111;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_round_24) {
//   castom_decimal src, origin, result;
//   // src = 2.7986531268974139743;
//   src.bits[0] = 0b11111110100100001101100101011111;
//   src.bits[1] = 0b10000100011001000010000111101000;
//   src.bits[2] = 0b00000000000000000000000000000001;
//   src.bits[3] = 0b00000000000100110000000000000000;
//   int check = castom_round(src, &result);
//   int check_origin = 0;
//   // origin = 3;
//   origin.bits[0] = 0b00000000000000000000000000000011;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_1) {
//   castom_decimal src, origin, result;
//   // src = 5.0;
//   src.bits[0] = 0b00000000000000000000000000110010;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 5;
//   origin.bits[0] = 0b00000000000000000000000000000101;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_2) {
//   castom_decimal src, origin, result;
//   // src = 3.4;
//   src.bits[0] = 0b00000000000000000000000000100010;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 3;
//   origin.bits[0] = 0b00000000000000000000000000000011;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_3) {
//   castom_decimal src, origin, result;
//   // src = 0.0;
//   src.bits[0] = 0b00000000000000000000000000000000;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 0;
//   origin.bits[0] = 0b00000000000000000000000000000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_4) {
//   castom_decimal src, origin, result;
//   // src = -2.4363463;
//   src.bits[0] = 0b00000001011100111100000111000111;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000001110000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = -3;
//   origin.bits[0] = 0b00000000000000000000000000000011;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_5) {
//   castom_decimal src, origin, result;
//   // src = -0.0;
//   src.bits[0] = 0b00000000000000000000000000000000;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 0;
//   origin.bits[0] = 0b00000000000000000000000000000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_6) {
//   castom_decimal src, origin, result;
//   // src = -0.45;
//   src.bits[0] = 0b00000000000000000000000000101101;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000100000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = -1;
//   origin.bits[0] = 0b00000000000000000000000000000001;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_7) {
//   castom_decimal src, origin, result;
//   // src = 652.34631;
//   src.bits[0] = 0b00000011111000110110011011000111;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000001010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 652;
//   origin.bits[0] = 0b00000000000000000000001010001100;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_8) {
//   castom_decimal src, origin, result;
//   // src = 4.97623323;
//   src.bits[0] = 0b00011101101010010010000100011011;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000010000000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 4;
//   origin.bits[0] = 0b00000000000000000000000000000100;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_9) {
//   castom_decimal src, origin, result;
//   // src = 65658654.59;
//   src.bits[0] = 0b10000111010110110010011111110011;
//   src.bits[1] = 0b00000000000000000000000000000001;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000100000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 65658654;
//   origin.bits[0] = 0b00000011111010011101111100011110;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_10) {
//   castom_decimal src, origin, result;
//   // src = -364748.110;
//   src.bits[0] = 0b00010101101111011001110101001110;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000110000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = -364749;
//   origin.bits[0] = 0b00000000000001011001000011001101;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_11) {
//   castom_decimal src, origin, result;
//   // src = 1.9874565432111;
//   src.bits[0] = 0b01101000011010011010001100101111;
//   src.bits[1] = 0b00000000000000000001001000010011;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000011010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 1;
//   origin.bits[0] = 0b00000000000000000000000000000001;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_12) {
//   castom_decimal src, origin, result;
//   // src = -98.78798789312;
//   src.bits[0] = 0b00010110010010101110101011000000;
//   src.bits[1] = 0b00000000000000000000100011111100;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000010110000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = -99;
//   origin.bits[0] = 0b00000000000000000000000001100011;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_13) {
//   castom_decimal src, origin, result;
//   // src = 999999999999999999911.3;
//   src.bits[0] = 0b10110010001111111111110010001001;
//   src.bits[1] = 0b00011001111000001100100110111010;
//   src.bits[2] = 0b00000000000000000000001000011110;
//   src.bits[3] = 0b00000000000000010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 999999999999999999911;
//   origin.bits[0] = 0b11011110100111111111111110100111;
//   origin.bits[1] = 0b00110101110010011010110111000101;
//   origin.bits[2] = 0b00000000000000000000000000110110;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_14) {
//   castom_decimal src, origin, result;
//   // src = -545454512454545.35265454545645;
//   src.bits[0] = 0b10000010111000100101101011101101;
//   src.bits[1] = 0b11111001111010000010010110101101;
//   src.bits[2] = 0b10110000001111101111000010010100;
//   src.bits[3] = 0b10000000000011100000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = -545454512454546;
//   origin.bits[0] = 0b10000110011101001011101110010010;
//   origin.bits[1] = 0b00000000000000011111000000010110;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_15) {
//   castom_decimal src, origin, result;
//   // src = 545454512454545.35265454545645;
//   src.bits[0] = 0b10000010111000100101101011101101;
//   src.bits[1] = 0b11111001111010000010010110101101;
//   src.bits[2] = 0b10110000001111101111000010010100;
//   src.bits[3] = 0b00000000000011100000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 545454512454545;
//   origin.bits[0] = 0b10000110011101001011101110010001;
//   origin.bits[1] = 0b00000000000000011111000000010110;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_16) {
//   castom_decimal src, origin, result;
//   // src = 7961327845421.879754123131254;
//   src.bits[0] = 0b01001110111001000011100101110110;
//   src.bits[1] = 0b01001011001101011010000111011001;
//   src.bits[2] = 0b00011001101110010111010010111111;
//   src.bits[3] = 0b00000000000011110000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 7961327845421;
//   origin.bits[0] = 0b10100100000111100100000000101101;
//   origin.bits[1] = 0b00000000000000000000011100111101;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_17) {
//   castom_decimal src, origin, result;
//   // src = 12345677.987654345678987654346;
//   src.bits[0] = 0b10010001000010101111010011001010;
//   src.bits[1] = 0b11000000010001011101010111110010;
//   src.bits[2] = 0b00100111111001000001101100000000;
//   src.bits[3] = 0b00000000000101010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 12345677;
//   origin.bits[0] = 0b00000000101111000110000101001101;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_18) {
//   castom_decimal src, origin, result;
//   // src = -12345677.987654345678987654346;
//   src.bits[0] = 0b10010001000010101111010011001010;
//   src.bits[1] = 0b11000000010001011101010111110010;
//   src.bits[2] = 0b00100111111001000001101100000000;
//   src.bits[3] = 0b10000000000101010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = -12345678;
//   origin.bits[0] = 0b00000000101111000110000101001110;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_19) {
//   castom_decimal src, origin, result;
//   // src = 87654323456.9876545678987653;
//   src.bits[0] = 0b00010001110011011101000110000101;
//   src.bits[1] = 0b11110101101111000110111111000000;
//   src.bits[2] = 0b00000010110101010000111100111111;
//   src.bits[3] = 0b00000000000100000000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 87654323456;
//   origin.bits[0] = 0b01101000100110101101010100000000;
//   origin.bits[1] = 0b00000000000000000000000000010100;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_20) {
//   castom_decimal src, origin, result;
//   // src = 336565445454313.859865545;
//   src.bits[0] = 0b00111110111111000101101111001001;
//   src.bits[1] = 0b00111111110101011110000010001011;
//   src.bits[2] = 0b00000000000000000100011101000101;
//   src.bits[3] = 0b00000000000010010000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 336565445454313;
//   origin.bits[0] = 0b10111111110100011110100111101001;
//   origin.bits[1] = 0b00000000000000010011001000011010;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_21) {
//   castom_decimal src, origin, result;
//   // src = -15456451234534;
//   src.bits[0] = 0b10111100010010010000101011100110;
//   src.bits[1] = 0b00000000000000000000111000001110;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000000000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = -15456451234534;
//   origin.bits[0] = 0b10111100010010010000101011100110;
//   origin.bits[1] = 0b00000000000000000000111000001110;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_22) {
//   castom_decimal src, origin, result;
//   // src = -0.42354543545;
//   src.bits[0] = 0b11011100100001110000101110111001;
//   src.bits[1] = 0b00000000000000000000000000001001;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000010110000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = -1;
//   origin.bits[0] = 0b00000000000000000000000000000001;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_23) {
//   castom_decimal src, origin, result;
//   // src = 79228162514264337593543950335;
//   src.bits[0] = 0b11111111111111111111111111111111;
//   src.bits[1] = 0b11111111111111111111111111111111;
//   src.bits[2] = 0b11111111111111111111111111111111;
//   src.bits[3] = 0b00000000000000000000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 79228162514264337593543950335;
//   origin.bits[0] = 0b11111111111111111111111111111111;
//   origin.bits[1] = 0b11111111111111111111111111111111;
//   origin.bits[2] = 0b11111111111111111111111111111111;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST

// START_TEST(castom_floor_24) {
//   castom_decimal src, origin, result;
//   // src = 2.7986531268974139743;
//   src.bits[0] = 0b11111110100100001101100101011111;
//   src.bits[1] = 0b10000100011001000010000111101000;
//   src.bits[2] = 0b00000000000000000000000000000001;
//   src.bits[3] = 0b00000000000100110000000000000000;
//   int check = castom_floor(src, &result);
//   int check_origin = 0;
//   // origin = 2;
//   origin.bits[0] = 0b00000000000000000000000000000010;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(check, check_origin);
// }
// END_TEST



// START_TEST(int_to_dec_1) {
//   castom_decimal result, origin;
//   int src = 1;
//   origin.bits[0] = 0b00000000000000000000000000000001;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_2) {
//   castom_decimal result, origin;
//   int src = 0;
//   origin.bits[0] = 0b00000000000000000000000000000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_3) {
//   castom_decimal result, origin;
//   int src = -1;
//   origin.bits[0] = 0b00000000000000000000000000000001;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_4) {
//   castom_decimal result, origin;
//   int src = 2147483647;
//   origin.bits[0] = 0b01111111111111111111111111111111;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_5) {
//   castom_decimal result, origin;
//   int src = -2147483647;
//   origin.bits[0] = 0b01111111111111111111111111111111;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_6) {
//   castom_decimal result, origin;
//   int src = -12345;
//   origin.bits[0] = 0b00000000000000000011000000111001;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_7) {
//   castom_decimal result, origin;
//   int src = -12345;
//   origin.bits[0] = 0b00000000000000000011000000111001;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_8) {
//   castom_decimal result, origin;
//   int src = 0;
//   origin.bits[0] = 0b00000000000000000000000000000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_9) {
//   castom_decimal result, origin;
//   int src = 45678;
//   origin.bits[0] = 0b00000000000000001011001001101110;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_10) {
//   castom_decimal result, origin;
//   int src = -45678;
//   origin.bits[0] = 0b00000000000000001011001001101110;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_11) {
//   castom_decimal result, origin;
//   int src = 5555555;
//   origin.bits[0] = 0b00000000010101001100010101100011;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_12) {
//   castom_decimal result, origin;
//   int src = -5555555;
//   origin.bits[0] = 0b00000000010101001100010101100011;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_13) {
//   castom_decimal result, origin;
//   int src = 127;
//   origin.bits[0] = 0b00000000000000000000000001111111;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_14) {
//   castom_decimal result, origin;
//   int src = -127;
//   origin.bits[0] = 0b00000000000000000000000001111111;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_15) {
//   castom_decimal result, origin;
//   int src = 34567898;
//   origin.bits[0] = 0b00000010000011110111011011011010;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_16) {
//   castom_decimal result, origin;
//   int src = -34567898;
//   origin.bits[0] = 0b00000010000011110111011011011010;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_17) {
//   castom_decimal result, origin;
//   int src = 999;
//   origin.bits[0] = 0b00000000000000000000001111100111;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_18) {
//   castom_decimal result, origin;
//   int src = -999;
//   origin.bits[0] = 0b00000000000000000000001111100111;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_19) {
//   castom_decimal result, origin;
//   int src = -3254754;
//   origin.bits[0] = 0b00000000001100011010100111100010;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b10000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_20) {
//   castom_decimal result, origin;
//   int src = 3436425;
//   origin.bits[0] = 0b00000000001101000110111110001001;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(int_to_dec_21) {
//   castom_decimal result, origin;
//   int src = 222222222;
//   origin.bits[0] = 0b00001101001111101101011110001110;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int result_error = 0;
//   int my_error = castom_from_int_to_decimal(src, &result);
//   ck_assert_int_eq(origin.bits[3], result.bits[3]);
//   ck_assert_int_eq(origin.bits[2], result.bits[2]);
//   ck_assert_int_eq(origin.bits[1], result.bits[1]);
//   ck_assert_int_eq(origin.bits[0], result.bits[0]);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_1) {
//   castom_decimal src;
//   src.bits[0] = 0b00000000000000000000000000110010;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000010000000000000000;
//   int result = 0;
//   int origin = 5;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_2) {
//   castom_decimal src;
//   src.bits[0] = 0b00000000000000000000000000100010;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000010000000000000000;
//   int result = 0;
//   int origin = 3;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_3) {
//   castom_decimal src;
//   src.bits[0] = 0b00000000000000000000000000000000;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000010000000000000000;
//   int result = 0;
//   int origin = 0;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_4) {
//   castom_decimal src;
//   src.bits[0] = 0b00000001011100111100000111000111;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000001110000000000000000;
//   int result = 0;
//   int origin = -2;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_5) {
//   castom_decimal src;
//   src.bits[0] = 0b00000000000000000000000000000000;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000010000000000000000;
//   int result = 0;
//   int origin = 0;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_7) {
//   castom_decimal src;
//   src.bits[0] = 0b00000011111000110110011011000111;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000001010000000000000000;
//   int result = 0;
//   int origin = 652;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_8) {
//   castom_decimal src;
//   src.bits[0] = 0b00011101101010010010000100011011;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000010000000000000000000;
//   int result = 0;
//   int origin = 4;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_9) {
//   castom_decimal src;
//   src.bits[0] = 0b10000111010110110010011111110011;
//   src.bits[1] = 0b00000000000000000000000000000001;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000100000000000000000;
//   int result = 0;
//   int origin = 65658654;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_10) {
//   castom_decimal src;
//   src.bits[0] = 0b00010101101111011001110101001110;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000110000000000000000;
//   int result = 0;
//   int origin = -364748;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_11) {
//   castom_decimal src;
//   src.bits[0] = 0b01101000011010011010001100101111;
//   src.bits[1] = 0b00000000000000000001001000010011;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000011010000000000000000;
//   int result = 0;
//   int origin = 1;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_12) {
//   castom_decimal src;
//   src.bits[0] = 0b00010110010010101110101011000000;
//   src.bits[1] = 0b00000000000000000000100011111100;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000010110000000000000000;
//   int result = 0;
//   int origin = -98;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_13) {
//   castom_decimal src;
//   src.bits[0] = 0b00111011100110101100100111111001;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000000010000000000000000;
//   int result = 0;
//   int origin = 99999999;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_14) {
//   castom_decimal src;
//   src.bits[0] = 0b11001010011010010001110011000010;
//   src.bits[1] = 0b10011001110101001010110100100110;
//   src.bits[2] = 0b10110000001111100010111010011101;
//   src.bits[3] = 0b10000000000101110000000000000000;
//   int result = 0;
//   int origin = -545445;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_15) {
//   castom_decimal src;
//   src.bits[0] = 0b11101010011100001110100101000111;
//   src.bits[1] = 0b10100010011001110000111100001010;
//   src.bits[2] = 0b10110000001111101111000100010000;
//   src.bits[3] = 0b00000000000101100000000000000000;
//   int result = 0;
//   int origin = 5454545;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_16) {
//   castom_decimal src;
//   src.bits[0] = 0b11101010001011100110110001010100;
//   src.bits[1] = 0b00100111000110111110101011111001;
//   src.bits[2] = 0b00011001101111000001110101101001;
//   src.bits[3] = 0b00000000000101000000000000000000;
//   int result = 0;
//   int origin = 79645421;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_17) {
//   castom_decimal src;
//   src.bits[0] = 0b10010001000010101111010011001010;
//   src.bits[1] = 0b11000000010001011101010111110010;
//   src.bits[2] = 0b00100111111001000001101100000000;
//   src.bits[3] = 0b00000000000101010000000000000000;
//   int result = 0;
//   int origin = 12345677;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_18) {
//   castom_decimal src;
//   src.bits[0] = 0b10010001000010101111010011001010;
//   src.bits[1] = 0b11000000010001011101010111110010;
//   src.bits[2] = 0b00100111111001000001101100000000;
//   src.bits[3] = 0b10000000000101010000000000000000;
//   int result = 0;
//   int origin = -12345677;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_19) {
//   castom_decimal src;
//   src.bits[0] = 0b10011100101100011101000110000101;
//   src.bits[1] = 0b01100001100101011101011101110110;
//   src.bits[2] = 0b00000000000000000000000011101010;
//   src.bits[3] = 0b00000000000100000000000000000000;
//   int result = 0;
//   int origin = 432356;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_20) {
//   castom_decimal src;
//   src.bits[0] = 0b01100001011111010111001111001001;
//   src.bits[1] = 0b00000000100111100100000111010001;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000010010000000000000000;
//   int result = 0;
//   int origin = 44545413;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_21) {
//   castom_decimal src;
//   src.bits[0] = 0b01011100000110001011011001101010;
//   src.bits[1] = 0b00000000000000000000000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b10000000000000000000000000000000;
//   int result = 0;
//   int origin = -1545123434;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_23) {
//   castom_decimal src;
//   src.bits[0] = 0b10101001101110110110011111111111;
//   src.bits[1] = 0b00001010111111101100000000000000;
//   src.bits[2] = 0b00000000000000000000000000000000;
//   src.bits[3] = 0b00000000000011000000000000000000;
//   int result = 0;
//   int origin = 792281;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_int_24) {
//   castom_decimal src;
//   src.bits[0] = 0b11111110100100001101100101011111;
//   src.bits[1] = 0b10000100011001000010000111101000;
//   src.bits[2] = 0b00000000000000000000000000000001;
//   src.bits[3] = 0b00000000000100110000000000000000;
//   int result = 0;
//   int origin = 2;
//   int origin_error = 0;
//   int my_error = castom_from_decimal_to_int(src, &result);
//   ck_assert_int_eq(origin, result);
//   ck_assert_int_eq(origin_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_1) {
//   castom_decimal number;
//   // decimal: 2.0
//   // float: 2
//   // int: 1073741824
//   number.bits[0] = 0b00000000000000000000000000010100;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000000010000000000000000;
//   int result_int = 1073741824;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_2) {
//   castom_decimal number;
//   // decimal: -0.8
//   // float: -0.8
//   // int: -1085485875
//   number.bits[0] = 0b00000000000000000000000000001000;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b10000000000000010000000000000000;
//   int result_int = -1085485875;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_3) {
//   castom_decimal number;
//   // decimal: 0
//   // float: 0
//   // int: 0
//   number.bits[0] = 0b00000000000000000000000000000000;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000000000000000000000000;
//   int result_int = 0;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_4) {
//   castom_decimal number;
//   // decimal: 1
//   // float: 1
//   // int: 1065353216
//   number.bits[0] = 0b00000000000000000000000000000001;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000000000000000000000000;
//   int result_int = 1065353216;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_5) {
//   castom_decimal number;
//   // decimal: 0.0
//   // float: 0
//   // int: -2147483648
//   number.bits[0] = 0b00000000000000000000000000000000;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b10000000000000010000000000000000;
//   int result_int = -2147483648;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_6) {
//   castom_decimal number;
//   // decimal: -1.75
//   // float: -1.75
//   // int: -1075838976
//   number.bits[0] = 0b00000000000000000000000010101111;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b10000000000000100000000000000000;
//   int result_int = -1075838976;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_7) {
//   castom_decimal number;
//   // decimal: 6521
//   // float: 6521
//   // int: 1170982912
//   number.bits[0] = 0b00000000000000000001100101111001;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000000000000000000000000;
//   int result_int = 1170982912;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_8) {
//   castom_decimal number;
//   // decimal: 4
//   // float: 4
//   // int: 1082130432
//   number.bits[0] = 0b00000000000000000000000000000100;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000000000000000000000000;
//   int result_int = 1082130432;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_9) {
//   castom_decimal number;
//   // decimal: 65658654
//   // float: 6.565866E+07
//   // int: 1283094472
//   number.bits[0] = 0b00000011111010011101111100011110;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000000000000000000000000;
//   int result_int = 1283094472;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_10) {
//   castom_decimal number;
//   // decimal: -364748
//   // float: -364748
//   // int: -927852160
//   number.bits[0] = 0b00000000000001011001000011001100;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b10000000000000000000000000000000;
//   int result_int = -927852160;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_11) {
//   castom_decimal number;
//   // decimal: 0.003
//   // float: 0.003
//   // int: 994352038
//   number.bits[0] = 0b00000000000000000000000000000011;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000000110000000000000000;
//   int result_int = 994352038;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_12) {
//   castom_decimal number;
//   // decimal: -9878798789
//   // float: -9.878798E+09
//   // int: -804047712
//   number.bits[0] = 0b01001100110100101000000111000101;
//   number.bits[1] = 0b00000000000000000000000000000010;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b10000000000000000000000000000000;
//   int result_int = -804047712;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_13) {
//   castom_decimal number;
//   // decimal: 9959999999999999999
//   // float: 9.96E+18
//   // int: 1594505479
//   number.bits[0] = 0b11001010111000111111111111111111;
//   number.bits[1] = 0b10001010001110010000011100111010;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000000000000000000000000;
//   int result_int = 1594505479;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_14) {
//   castom_decimal number;
//   // decimal: 18446744073709551615
//   // float: 1.844674E+19
//   // int: 1602224128
//   number.bits[0] = 0b11111111111111111111111111111111;
//   number.bits[1] = 0b11111111111111111111111111111111;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000000000000000000000000;
//   int result_int = 1602224128;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_17) {
//   castom_decimal number;
//   // decimal: -5454545545352456454545645464
//   // float: -5.454546E+27
//   // int: -309526744
//   number.bits[0] = 0b10001000100000001001111110011000;
//   number.bits[1] = 0b10000010011101100000001010011001;
//   number.bits[2] = 0b00010001100111111110010011110010;
//   number.bits[3] = 0b10000000000000000000000000000000;
//   int result_int = -309526744;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_18) {
//   castom_decimal number;
//   // decimal: 79228162514264337593543950335
//   // float: 7.922816E+28
//   // int: 1870659584
//   number.bits[0] = 0b11111111111111111111111111111111;
//   number.bits[1] = 0b11111111111111111111111111111111;
//   number.bits[2] = 0b11111111111111111111111111111111;
//   number.bits[3] = 0b00000000000000000000000000000000;
//   int result_int = 1870659584;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_19) {
//   castom_decimal number;
//   // decimal: 1234.5677987654345678987654346
//   // float: 1234.568
//   // int: 1150964267
//   number.bits[0] = 0b10010001000010101111010011001010;
//   number.bits[1] = 0b11000000010001011101010111110010;
//   number.bits[2] = 0b00100111111001000001101100000000;
//   number.bits[3] = 0b00000000000110010000000000000000;
//   int result_int = 1150964267;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_20) {
//   castom_decimal number;
//   // decimal: -123458677.98765434567898765435
//   // float: -1.234587E+08
//   // int: -856982897
//   number.bits[0] = 0b10111001000000010001100001111011;
//   number.bits[1] = 0b01101110100110001001011011101100;
//   number.bits[2] = 0b00100111111001000100001100110010;
//   number.bits[3] = 0b10000000000101000000000000000000;
//   int result_int = -856982897;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_21) {
//   castom_decimal number;
//   // decimal: 123445677.98765434567898765435
//   // float: 1.234457E+08
//   // int: 1290499126
//   number.bits[0] = 0b00110100100000010001100001111011;
//   number.bits[1] = 0b01001010011100100010011000011110;
//   number.bits[2] = 0b00100111111000110010111111101001;
//   number.bits[3] = 0b00000000000101000000000000000000;
//   int result_int = 1290499126;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_22) {
//   castom_decimal number;
//   // decimal: -12345677.987654533456789876543
//   // float: -1.234568E+07
//   // int: -885235378
//   number.bits[0] = 0b11111110001111011010111100111111;
//   number.bits[1] = 0b11000000010001101000000010111010;
//   number.bits[2] = 0b00100111111001000001101100000000;
//   number.bits[3] = 0b10000000000101010000000000000000;
//   int result_int = -885235378;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_23) {
//   castom_decimal number;
//   // decimal: 0.0000000000000000001
//   // float: 1E-19
//   // int: 535567946
//   number.bits[0] = 0b00000000000000000000000000000001;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000100110000000000000000;
//   int result_int = 535567946;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_24) {
//   castom_decimal number;
//   // decimal: 0.0000000000000000000000000001
//   // float: 1E-28
//   // int: 285050806
//   number.bits[0] = 0b00000000000000000000000000000001;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000111000000000000000000;
//   int result_int = 285050806;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_25) {
//   castom_decimal number;
//   // decimal: 0.0000000000000000000000000000
//   // float: 0
//   // int: -2147483648
//   number.bits[0] = 0b00000000000000000000000000000000;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b10000000000111000000000000000000;
//   int result_int = -2147483648;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_26) {
//   castom_decimal number;
//   // decimal: -79228162514264337593543950335
//   // float: -7.922816E+28
//   // int: -276824064
//   number.bits[0] = 0b11111111111111111111111111111111;
//   number.bits[1] = 0b11111111111111111111111111111111;
//   number.bits[2] = 0b11111111111111111111111111111111;
//   number.bits[3] = 0b10000000000000000000000000000000;
//   int result_int = -276824064;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_27) {
//   castom_decimal number;
//   // decimal: -792.28162514264337593543950335
//   // float: -792.2816
//   // int: -1002040826
//   number.bits[0] = 0b11111111111111111111111111111111;
//   number.bits[1] = 0b11111111111111111111111111111111;
//   number.bits[2] = 0b11111111111111111111111111111111;
//   number.bits[3] = 0b10000000000110100000000000000000;
//   int result_int = -1002040826;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_28) {
//   castom_decimal number;
//   // decimal: -79228162514264337593543950335
//   // float: -7.922816E+28
//   // int: -276824064
//   number.bits[0] = 0b11111111111111111111111111111111;
//   number.bits[1] = 0b11111111111111111111111111111111;
//   number.bits[2] = 0b11111111111111111111111111111111;
//   number.bits[3] = 0b10000000000000000000000000000000;
//   int result_int = -276824064;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_29) {
//   castom_decimal number;
//   // decimal: 2.7986531268974139743
//   // float: 2.798653
//   // int: 1077091618
//   number.bits[0] = 0b11111110100100001101100101011111;
//   number.bits[1] = 0b10000100011001000010000111101000;
//   number.bits[2] = 0b00000000000000000000000000000001;
//   number.bits[3] = 0b00000000000100110000000000000000;
//   int result_int = 1077091618;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_31) {
//   castom_decimal number;
//   // decimal: 5.4564654654864768465454654846
//   // float: 5.456465
//   // int: 1085184861
//   number.bits[0] = 0b01101110100110100110010101111110;
//   number.bits[1] = 0b11100010111000110111110100101010;
//   number.bits[2] = 0b10110000010011101101001100001111;
//   number.bits[3] = 0b00000000000111000000000000000000;
//   int result_int = 1085184861;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_33) {
//   castom_decimal number;
//   // decimal: -79228162514264337593543950330
//   // float: -7.922816E+28
//   // int: -276824064
//   number.bits[0] = 0b11111111111111111111111111111010;
//   number.bits[1] = 0b11111111111111111111111111111111;
//   number.bits[2] = 0b11111111111111111111111111111111;
//   number.bits[3] = 0b10000000000000000000000000000000;
//   int result_int = -276824064;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_34) {
//   castom_decimal number;
//   // decimal: 32323465785678987654
//   // float: 3.232346E+19
//   // int: 1608534530
//   number.bits[0] = 0b00000000111000111000000110000110;
//   number.bits[1] = 0b11000000100101000000010011100000;
//   number.bits[2] = 0b00000000000000000000000000000001;
//   number.bits[3] = 0b00000000000000000000000000000000;
//   int result_int = 1608534530;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_35) {
//   castom_decimal number;
//   // decimal: -784510454.7989898652154545652
//   // float: -7.845105E+08
//   // int: -834991432
//   number.bits[0] = 0b00110101111110110100010111110100;
//   number.bits[1] = 0b10110111000111111011101111011100;
//   number.bits[2] = 0b00011001010110010101000110000001;
//   number.bits[3] = 0b10000000000100110000000000000000;
//   int result_int = -834991432;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(dec_to_float_36) {
//   castom_decimal number;
//   // decimal: 0.324524
//   // float: 0.324524
//   // int: 1051076610
//   number.bits[0] = 0b00000000000001001111001110101100;
//   number.bits[1] = 0b00000000000000000000000000000000;
//   number.bits[2] = 0b00000000000000000000000000000000;
//   number.bits[3] = 0b00000000000001100000000000000000;
//   int result_int = 1051076610;
//   int result_error = 0;
//   float my_float;
//   int my_error = castom_from_decimal_to_float(number, &my_float);
//   int my_int = *(int *)(void *)&my_float;
//   ck_assert_int_eq(result_int, my_int);
//   ck_assert_int_eq(result_error, my_error);
// }
// END_TEST

// START_TEST(castom_from_float_to_decimal_1) {
//   castom_decimal val;
//   castom_from_float_to_decimal(0.03F, &val);
//   ck_assert_int_eq(val.bits[0], 3);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 131072);
//   castom_from_float_to_decimal(127.1234F, &val);
//   ck_assert_int_eq(val.bits[0], 1271234);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 262144);
// }
// END_TEST

// START_TEST(castom_from_float_to_decimal_2) {
//   castom_decimal val;
//   castom_from_float_to_decimal(22.14836E+03F, &val);
//   ck_assert_int_eq(val.bits[0], 2214836);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 131072);
// }
// END_TEST

// START_TEST(castom_from_float_to_decimal_3) {
//   castom_decimal val;
//   castom_from_float_to_decimal(1.02E+09F, &val);
//   ck_assert_int_eq(val.bits[0], 1020000000);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 0);
// }
// END_TEST

// START_TEST(castom_from_float_to_decimal_4) {
//   castom_decimal val;
//   float a = 1.0F / 0.0F;
//   int err_check = castom_from_float_to_decimal(a, &val);
//   ck_assert_int_eq(err_check, CONVERTING_ERROR);
//   ck_assert_int_eq(val.bits[0], 0);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 0);
// }
// END_TEST

// START_TEST(castom_from_float_to_decimal_5) {
//   castom_decimal val;
//   float a = -1.0F / 0.0F;
//   int err_check = castom_from_float_to_decimal(a, &val);
//   ck_assert_int_eq(err_check, CONVERTING_ERROR);
//   ck_assert_int_eq(val.bits[0], 0);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], -2147483648);
// }
// END_TEST

// START_TEST(castom_from_float_to_decimal_6) {
//   castom_decimal val;
//   float a = NAN;
//   int err_check = castom_from_float_to_decimal(a, &val);
//   ck_assert_int_eq(err_check, CONVERTING_ERROR);
//   ck_assert_int_eq(val.bits[0], 0);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 0);
// }
// END_TEST

// START_TEST(castom_from_float_to_decimal_7) {
//   castom_decimal val;
//   castom_from_float_to_decimal(0.0F, &val);
//   ck_assert_int_eq(val.bits[0], 0);
//   ck_assert_int_eq(val.bits[1], 0);
//   ck_assert_int_eq(val.bits[2], 0);
//   ck_assert_int_eq(val.bits[3], 0);
// }
// END_TEST

