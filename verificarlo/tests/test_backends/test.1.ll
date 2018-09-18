; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@data = common global [1000 x double] zeroinitializer, align 16
@.str = private unnamed_addr constant [9 x i8] c"TEST>%g\0A\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"N >= 1\00", align 1
@.str.2 = private unnamed_addr constant [7 x i8] c"test.c\00", align 1
@__PRETTY_FUNCTION__.compute_mean = private unnamed_addr constant [35 x i8] c"double compute_mean(int, double *)\00", align 1
@.str.3 = private unnamed_addr constant [7 x i8] c"N >= 2\00", align 1
@__PRETTY_FUNCTION__.compute_variance = private unnamed_addr constant [47 x i8] c"double compute_variance(int, double, double *)\00", align 1

; Function Attrs: noinline nounwind uwtable
define double @operate(double, double) #0 {
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  store double %0, double* %3, align 8
  store double %1, double* %4, align 8
  %5 = load double, double* %3, align 8
  %6 = load double, double* %4, align 8
  %7 = fdiv double %5, %6
  ret double %7
}

; Function Attrs: noinline nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @srand(i32 0) #4
  store i32 0, i32* %2, align 4
  br label %3

; <label>:3:                                      ; preds = %13, %0
  %4 = load i32, i32* %2, align 4
  %5 = icmp slt i32 %4, 50
  br i1 %5, label %6, label %16

; <label>:6:                                      ; preds = %3
  %7 = call i32 @rand() #4
  %8 = sitofp i32 %7 to double
  %9 = fdiv double %8, 0x41DFFFFFFFC00000
  %10 = call i32 @rand() #4
  %11 = sitofp i32 %10 to double
  %12 = fdiv double %11, 0x41DFFFFFFFC00000
  call void @do_test(double %9, double %12)
  br label %13

; <label>:13:                                     ; preds = %6
  %14 = load i32, i32* %2, align 4
  %15 = add nsw i32 %14, 1
  store i32 %15, i32* %2, align 4
  br label %3

; <label>:16:                                     ; preds = %3
  ret i32 0
}

; Function Attrs: nounwind
declare void @srand(i32) #1

; Function Attrs: noinline nounwind uwtable
define internal void @do_test(double, double) #0 {
  %3 = alloca double, align 8
  %4 = alloca double, align 8
  %5 = alloca i32, align 4
  %6 = alloca double, align 8
  store double %0, double* %3, align 8
  store double %1, double* %4, align 8
  store i32 0, i32* %5, align 4
  br label %7

; <label>:7:                                      ; preds = %17, %2
  %8 = load i32, i32* %5, align 4
  %9 = icmp slt i32 %8, 1000
  br i1 %9, label %10, label %20

; <label>:10:                                     ; preds = %7
  %11 = load double, double* %3, align 8
  %12 = load double, double* %4, align 8
  %13 = call double @operate(double %11, double %12)
  %14 = load i32, i32* %5, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [1000 x double], [1000 x double]* @data, i64 0, i64 %15
  store double %13, double* %16, align 8
  br label %17

; <label>:17:                                     ; preds = %10
  %18 = load i32, i32* %5, align 4
  %19 = add nsw i32 %18, 1
  store i32 %19, i32* %5, align 4
  br label %7

; <label>:20:                                     ; preds = %7
  %21 = call double @compute_sig(i32 1000, double* getelementptr inbounds ([1000 x double], [1000 x double]* @data, i32 0, i32 0))
  store double %21, double* %6, align 8
  %22 = load double, double* %6, align 8
  %23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i32 0, i32 0), double %22)
  ret void
}

; Function Attrs: nounwind
declare i32 @rand() #1

; Function Attrs: noinline nounwind uwtable
define internal double @compute_sig(i32, double*) #0 {
  %3 = alloca i32, align 4
  %4 = alloca double*, align 8
  %5 = alloca double, align 8
  %6 = alloca double, align 8
  store i32 %0, i32* %3, align 4
  store double* %1, double** %4, align 8
  %7 = load i32, i32* %3, align 4
  %8 = load double*, double** %4, align 8
  %9 = call double @compute_mean(i32 %7, double* %8)
  store double %9, double* %5, align 8
  %10 = load i32, i32* %3, align 4
  %11 = load double, double* %5, align 8
  %12 = load double*, double** %4, align 8
  %13 = call double @compute_variance(i32 %10, double %11, double* %12)
  %14 = call double @sqrt(double %13) #4
  store double %14, double* %6, align 8
  %15 = load double, double* %6, align 8
  %16 = load double, double* %5, align 8
  %17 = fdiv double %15, %16
  %18 = call double @log2(double %17) #4
  %19 = fsub double -0.000000e+00, %18
  ret double %19
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind uwtable
define internal double @compute_mean(i32, double*) #0 {
  %3 = alloca i32, align 4
  %4 = alloca double*, align 8
  %5 = alloca double, align 8
  %6 = alloca double, align 8
  %7 = alloca double, align 8
  %8 = alloca double, align 8
  %9 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store double* %1, double** %4, align 8
  %10 = load i32, i32* %3, align 4
  %11 = icmp sge i32 %10, 1
  br i1 %11, label %12, label %13

; <label>:12:                                     ; preds = %2
  br label %14

; <label>:13:                                     ; preds = %2
  call void @__assert_fail(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i32 0, i32 0), i32 10, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.compute_mean, i32 0, i32 0)) #5
  unreachable

; <label>:14:                                     ; preds = %12
  %15 = load double*, double** %4, align 8
  %16 = getelementptr inbounds double, double* %15, i64 0
  %17 = load double, double* %16, align 8
  store double %17, double* %5, align 8
  store double 0.000000e+00, double* %6, align 8
  store i32 1, i32* %9, align 4
  br label %18

; <label>:18:                                     ; preds = %39, %14
  %19 = load i32, i32* %9, align 4
  %20 = load i32, i32* %3, align 4
  %21 = icmp slt i32 %19, %20
  br i1 %21, label %22, label %42

; <label>:22:                                     ; preds = %18
  %23 = load double*, double** %4, align 8
  %24 = load i32, i32* %9, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds double, double* %23, i64 %25
  %27 = load double, double* %26, align 8
  %28 = load double, double* %6, align 8
  %29 = fsub double %27, %28
  store double %29, double* %7, align 8
  %30 = load double, double* %5, align 8
  %31 = load double, double* %7, align 8
  %32 = fadd double %30, %31
  store double %32, double* %8, align 8
  %33 = load double, double* %8, align 8
  %34 = load double, double* %5, align 8
  %35 = fsub double %33, %34
  %36 = load double, double* %7, align 8
  %37 = fsub double %35, %36
  store double %37, double* %6, align 8
  %38 = load double, double* %8, align 8
  store double %38, double* %5, align 8
  br label %39

; <label>:39:                                     ; preds = %22
  %40 = load i32, i32* %9, align 4
  %41 = add nsw i32 %40, 1
  store i32 %41, i32* %9, align 4
  br label %18

; <label>:42:                                     ; preds = %18
  %43 = load double, double* %5, align 8
  %44 = load i32, i32* %3, align 4
  %45 = sitofp i32 %44 to double
  %46 = fdiv double %43, %45
  ret double %46
}

; Function Attrs: nounwind
declare double @sqrt(double) #1

; Function Attrs: noinline nounwind uwtable
define internal double @compute_variance(i32, double, double*) #0 {
  %4 = alloca i32, align 4
  %5 = alloca double, align 8
  %6 = alloca double*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca double, align 8
  %10 = alloca double, align 8
  %11 = alloca double, align 8
  store i32 %0, i32* %4, align 4
  store double %1, double* %5, align 8
  store double* %2, double** %6, align 8
  %12 = load i32, i32* %4, align 4
  %13 = icmp sge i32 %12, 2
  br i1 %13, label %14, label %15

; <label>:14:                                     ; preds = %3
  br label %16

; <label>:15:                                     ; preds = %3
  call void @__assert_fail(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i32 0, i32 0), i32 28, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @__PRETTY_FUNCTION__.compute_variance, i32 0, i32 0)) #5
  unreachable

; <label>:16:                                     ; preds = %14
  store i32 0, i32* %8, align 4
  %17 = load double, double* %5, align 8
  store double %17, double* %9, align 8
  store double 0.000000e+00, double* %10, align 8
  store i32 0, i32* %7, align 4
  br label %18

; <label>:18:                                     ; preds = %49, %16
  %19 = load i32, i32* %7, align 4
  %20 = load i32, i32* %4, align 4
  %21 = icmp slt i32 %19, %20
  br i1 %21, label %22, label %52

; <label>:22:                                     ; preds = %18
  %23 = load i32, i32* %8, align 4
  %24 = add nsw i32 %23, 1
  store i32 %24, i32* %8, align 4
  %25 = load double*, double** %6, align 8
  %26 = load i32, i32* %7, align 4
  %27 = sext i32 %26 to i64
  %28 = getelementptr inbounds double, double* %25, i64 %27
  %29 = load double, double* %28, align 8
  %30 = load double, double* %9, align 8
  %31 = fsub double %29, %30
  store double %31, double* %11, align 8
  %32 = load double, double* %11, align 8
  %33 = load i32, i32* %8, align 4
  %34 = sitofp i32 %33 to double
  %35 = fdiv double %32, %34
  %36 = load double, double* %9, align 8
  %37 = fadd double %36, %35
  store double %37, double* %9, align 8
  %38 = load double, double* %11, align 8
  %39 = load double*, double** %6, align 8
  %40 = load i32, i32* %7, align 4
  %41 = sext i32 %40 to i64
  %42 = getelementptr inbounds double, double* %39, i64 %41
  %43 = load double, double* %42, align 8
  %44 = load double, double* %9, align 8
  %45 = fsub double %43, %44
  %46 = fmul double %38, %45
  %47 = load double, double* %10, align 8
  %48 = fadd double %47, %46
  store double %48, double* %10, align 8
  br label %49

; <label>:49:                                     ; preds = %22
  %50 = load i32, i32* %7, align 4
  %51 = add nsw i32 %50, 1
  store i32 %51, i32* %7, align 4
  br label %18

; <label>:52:                                     ; preds = %18
  %53 = load double, double* %10, align 8
  %54 = load i32, i32* %8, align 4
  %55 = sub nsw i32 %54, 1
  %56 = sitofp i32 %55 to double
  %57 = fdiv double %53, %56
  ret double %57
}

; Function Attrs: nounwind
declare double @log2(double) #1

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }
attributes #5 = { noreturn nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.1-10 (tags/RELEASE_401/final)"}
