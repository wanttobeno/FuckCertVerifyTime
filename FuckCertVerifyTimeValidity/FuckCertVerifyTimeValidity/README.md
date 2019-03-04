
##### Fork Form
[https://github.com/hzqst/FuckCertVerifyTimeValidity](https://github.com/hzqst/FuckCertVerifyTimeValidity)

# FuckCertVerifyTimeValidity
This tiny project prevents the signtool from verifing cert time validity and let you sign your bin with outdated cert without changing system time manually

# What it does
it install hook into ```crypt32!CertVerifyTimeValidity``` and make it always return 0.
and make ```kernel32!GetLocalTime``` return what you want as you can add "-fuckyear 2011" to signtool's commandline to sign a cert from year 2011.

# Build
Visual Studio 2015 / 2017, you know how to build.

# Installation
Use LordPE to add an import entry ```FuckCertVerifyTimeValidity.dll!test``` for signtool/DSignTool/CSignTool.

# Reference
https://github.com/Microsoft/Detours is used to hook system apis
