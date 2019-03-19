open Css;

type themeSpacing = {
  xsmall: int,
  small: int,
  smedium: int,
  medium: int,
  large: int,
  xlarge: int,
};

type themeColors = {
  greyDefault: color,
  greySecondary: color,
  bgColor: color,
};

let spacingUnitPx = 6;

let pageMaxWidth = 1488;

let colors: themeColors = {
  greyDefault: hex("111"),
  greySecondary: hex("4a4a4a"),
  bgColor: hex("fafafa"),
};

let spacingPx: themeSpacing = {
  xsmall: spacingUnitPx,
  small: spacingUnitPx * 2,
  smedium: spacingUnitPx * 3,
  medium: spacingUnitPx * 4,
  large: spacingUnitPx * 6,
  xlarge: spacingUnitPx * 7,
};
