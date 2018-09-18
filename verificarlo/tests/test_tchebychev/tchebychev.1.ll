; ModuleID = 'tchebychev.c'
source_filename = "tchebychev.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@coefs = global [10 x double] [double -2.000000e+02, double 6.600000e+03, double -8.448000e+04, double 5.491200e+05, double -2.050048e+06, double 4.659200e+06, double -6.553600e+06, double 5.570560e+06, double -2.621440e+06, double 5.242880e+05], align 16
@.str = private unnamed_addr constant [10 x i8] c"argc == 2\00", align 1
@.str.1 = private unnamed_addr constant [13 x i8] c"tchebychev.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [23 x i8] c"int main(int, char **)\00", align 1
@.str.2 = private unnamed_addr constant [7 x i8] c"%g %g\0A\00", align 1

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
  %22 = fmul double %20, %21
  store double %22, double* %8, align 8
  %23 = load double, double* %8, align 8
  store double %23, double* %9, align 8
  store i32 0, i32* %10, align 4
  br label %24

; <label>:24:                                     ; preds = %39, %15
  %25 = load i32, i32* %10, align 4
  %26 = icmp slt i32 %25, 10
  br i1 %26, label %27, label %42

; <label>:27:                                     ; preds = %24
  %28 = load i32, i32* %10, align 4
  %29 = sext i32 %28 to i64
  %30 = getelementptr inbounds [10 x double], [10 x double]* @coefs, i64 0, i64 %29
  %31 = load double, double* %30, align 8
  %32 = load double, double* %9, align 8
  %33 = fmul double %31, %32
  %34 = load double, double* %7, align 8
  %35 = fadd double %34, %33
  store double %35, double* %7, align 8
  %36 = load double, double* %8, align 8
  %37 = load double, double* %9, align 8
  %38 = fmul double %37, %36
  store double %38, double* %9, align 8
  br label %39

; <label>:39:                                     ; preds = %27
  %40 = load i32, i32* %10, align 4
  %41 = add nsw i32 %40, 1
  store i32 %41, i32* %10, align 4
  br label %24

; <label>:42:                                     ; preds = %24
  %43 = load double, double* %6, align 8
  %44 = load double, double* %7, align 8
  %45 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i32 0, i32 0), double %43, double %44)
  %46 = load i32, i32* %3, align 4
  ret i32 %46
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
