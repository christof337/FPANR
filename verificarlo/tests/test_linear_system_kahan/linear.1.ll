; ModuleID = 'linear.c'
source_filename = "linear.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@main.A = private unnamed_addr constant [4 x double] [double 2.161000e-01, double 1.441000e-01, double 1.296900e+00, double 8.648000e-01], align 16
@main.B = private unnamed_addr constant [2 x double] [double 1.440000e-01, double 8.642000e-01], align 16
@.str = private unnamed_addr constant [13 x i8] c"%.16e %.16e\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define void @solve(double*, double*, double*) #0 {
  %4 = alloca double*, align 8
  %5 = alloca double*, align 8
  %6 = alloca double*, align 8
  %7 = alloca double, align 8
  %8 = alloca double, align 8
  %9 = alloca double, align 8
  store double* %0, double** %4, align 8
  store double* %1, double** %5, align 8
  store double* %2, double** %6, align 8
  %10 = load double*, double** %4, align 8
  %11 = getelementptr inbounds double, double* %10, i64 0
  %12 = load double, double* %11, align 8
  %13 = load double*, double** %4, align 8
  %14 = getelementptr inbounds double, double* %13, i64 3
  %15 = load double, double* %14, align 8
  %16 = fmul double %12, %15
  %17 = load double*, double** %4, align 8
  %18 = getelementptr inbounds double, double* %17, i64 2
  %19 = load double, double* %18, align 8
  %20 = load double*, double** %4, align 8
  %21 = getelementptr inbounds double, double* %20, i64 1
  %22 = load double, double* %21, align 8
  %23 = fmul double %19, %22
  %24 = fsub double %16, %23
  store double %24, double* %7, align 8
  %25 = load double*, double** %5, align 8
  %26 = getelementptr inbounds double, double* %25, i64 0
  %27 = load double, double* %26, align 8
  %28 = load double*, double** %4, align 8
  %29 = getelementptr inbounds double, double* %28, i64 3
  %30 = load double, double* %29, align 8
  %31 = fmul double %27, %30
  %32 = load double*, double** %5, align 8
  %33 = getelementptr inbounds double, double* %32, i64 1
  %34 = load double, double* %33, align 8
  %35 = load double*, double** %4, align 8
  %36 = getelementptr inbounds double, double* %35, i64 1
  %37 = load double, double* %36, align 8
  %38 = fmul double %34, %37
  %39 = fsub double %31, %38
  store double %39, double* %8, align 8
  %40 = load double*, double** %4, align 8
  %41 = getelementptr inbounds double, double* %40, i64 0
  %42 = load double, double* %41, align 8
  %43 = load double*, double** %5, align 8
  %44 = getelementptr inbounds double, double* %43, i64 1
  %45 = load double, double* %44, align 8
  %46 = fmul double %42, %45
  %47 = load double*, double** %4, align 8
  %48 = getelementptr inbounds double, double* %47, i64 2
  %49 = load double, double* %48, align 8
  %50 = load double*, double** %5, align 8
  %51 = getelementptr inbounds double, double* %50, i64 0
  %52 = load double, double* %51, align 8
  %53 = fmul double %49, %52
  %54 = fsub double %46, %53
  store double %54, double* %9, align 8
  %55 = load double, double* %8, align 8
  %56 = load double, double* %7, align 8
  %57 = fdiv double %55, %56
  %58 = load double*, double** %6, align 8
  %59 = getelementptr inbounds double, double* %58, i64 0
  store double %57, double* %59, align 8
  %60 = load double, double* %9, align 8
  %61 = load double, double* %7, align 8
  %62 = fdiv double %60, %61
  %63 = load double*, double** %6, align 8
  %64 = getelementptr inbounds double, double* %63, i64 1
  store double %62, double* %64, align 8
  ret void
}

; Function Attrs: noinline nounwind uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca [4 x double], align 16
  %7 = alloca [2 x double], align 16
  %8 = alloca [2 x double], align 16
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %9 = bitcast [4 x double]* %6 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %9, i8* bitcast ([4 x double]* @main.A to i8*), i64 32, i32 16, i1 false)
  %10 = bitcast [2 x double]* %7 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %10, i8* bitcast ([2 x double]* @main.B to i8*), i64 16, i32 16, i1 false)
  %11 = bitcast [2 x double]* %8 to i8*
  call void @llvm.memset.p0i8.i64(i8* %11, i8 0, i64 16, i32 16, i1 false)
  %12 = getelementptr inbounds [4 x double], [4 x double]* %6, i32 0, i32 0
  %13 = getelementptr inbounds [2 x double], [2 x double]* %7, i32 0, i32 0
  %14 = getelementptr inbounds [2 x double], [2 x double]* %8, i32 0, i32 0
  call void @solve(double* %12, double* %13, double* %14)
  %15 = getelementptr inbounds [2 x double], [2 x double]* %8, i64 0, i64 0
  %16 = load double, double* %15, align 16
  %17 = getelementptr inbounds [2 x double], [2 x double]* %8, i64 0, i64 1
  %18 = load double, double* %17, align 8
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), double %16, double %18)
  ret i32 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i32, i1) #1

declare i32 @printf(i8*, ...) #2

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.1-10 (tags/RELEASE_401/final)"}
