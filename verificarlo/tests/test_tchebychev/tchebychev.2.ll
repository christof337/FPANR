; ModuleID = 'tchebychev.1.ll'
source_filename = "tchebychev.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@coefs = global [10 x double] [double -2.000000e+02, double 6.600000e+03, double -8.448000e+04, double 5.491200e+05, double -2.050048e+06, double 4.659200e+06, double -6.553600e+06, double 5.570560e+06, double -2.621440e+06, double 5.242880e+05], align 16
@.str = private unnamed_addr constant [10 x i8] c"argc == 2\00", align 1
@.str.1 = private unnamed_addr constant [13 x i8] c"tchebychev.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [23 x i8] c"int main(int, char **)\00", align 1
@.str.2 = private unnamed_addr constant [7 x i8] c"%g %g\0A\00", align 1
@_vfc_current_mca_interface = external global { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }

; Function Attrs: noinline nounwind uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca double, align 8
  %7 = alloca double, align 8
  %8 = alloca double, align 8
  %9 = alloca double, align 8
  %10 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %11 = load i32, i32* %4, align 4
  %12 = icmp eq i32 %11, 2
  br i1 %12, label %13, label %14

; <label>:13:                                     ; preds = %2
  br label %15

; <label>:14:                                     ; preds = %2
  call void @__assert_fail(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i32 0, i32 0), i32 22, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @__PRETTY_FUNCTION__.main, i32 0, i32 0)) #4
  unreachable

; <label>:15:                                     ; preds = %13
  %16 = load i8**, i8*** %5, align 8
  %17 = getelementptr inbounds i8*, i8** %16, i64 1
  %18 = load i8*, i8** %17, align 8
  %19 = call double @atof(i8* %18) #5
  store double %19, double* %6, align 8
  store double 1.000000e+00, double* %7, align 8
  %20 = load double, double* %6, align 8
  %21 = load double, double* %6, align 8
  %22 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 6)
  %23 = call double %22(double %20, double %21)
  store double %23, double* %8, align 8
  %24 = load double, double* %8, align 8
  store double %24, double* %9, align 8
  store i32 0, i32* %10, align 4
  br label %25

; <label>:25:                                     ; preds = %43, %15
  %26 = load i32, i32* %10, align 4
  %27 = icmp slt i32 %26, 10
  br i1 %27, label %28, label %46

; <label>:28:                                     ; preds = %25
  %29 = load i32, i32* %10, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [10 x double], [10 x double]* @coefs, i64 0, i64 %30
  %32 = load double, double* %31, align 8
  %33 = load double, double* %9, align 8
  %34 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 6)
  %35 = call double %34(double %32, double %33)
  %36 = load double, double* %7, align 8
  %37 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 4)
  %38 = call double %37(double %36, double %35)
  store double %38, double* %7, align 8
  %39 = load double, double* %8, align 8
  %40 = load double, double* %9, align 8
  %41 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 6)
  %42 = call double %41(double %40, double %39)
  store double %42, double* %9, align 8
  br label %43

; <label>:43:                                     ; preds = %28
  %44 = load i32, i32* %10, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, i32* %10, align 4
  br label %25

; <label>:46:                                     ; preds = %25
  %47 = load double, double* %6, align 8
  %48 = load double, double* %7, align 8
  %49 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i32 0, i32 0), double %47, double %48)
  %50 = load i32, i32* %3, align 4
  ret i32 %50
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #1

; Function Attrs: nounwind readonly
declare double @atof(i8*) #2

declare i32 @printf(i8*, ...) #3

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind }
attributes #5 = { nounwind readonly }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.1-10 (tags/RELEASE_401/final)"}
