; ModuleID = 'rr_mode.1.ll'
source_filename = "rr_mode.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [7 x i8] c"%.13a\0A\00", align 1
@_vfc_current_mca_interface = external global { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }

; Function Attrs: noinline nounwind uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca double, align 8
  %7 = alloca double, align 8
  %8 = alloca double, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  store double 5.242880e+05, double* %6, align 8
  store double 0xC2D0000002000000, double* %7, align 8
  %9 = load double, double* %6, align 8
  %10 = load double, double* %7, align 8
  %11 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 4)
  %12 = call double %11(double %9, double %10)
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str, i32 0, i32 0), double %12)
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.1-10 (tags/RELEASE_401/final)"}
