; ModuleID = 'linear.1.ll'
source_filename = "linear.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@main.A = private unnamed_addr constant [4 x double] [double 2.161000e-01, double 1.441000e-01, double 1.296900e+00, double 8.648000e-01], align 16
@main.B = private unnamed_addr constant [2 x double] [double 1.440000e-01, double 8.642000e-01], align 16
@.str = private unnamed_addr constant [13 x i8] c"%.16e %.16e\0A\00", align 1
@_vfc_current_mca_interface = external global { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }

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
  %16 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 6)
  %17 = call double %16(double %12, double %15)
  %18 = load double*, double** %4, align 8
  %19 = getelementptr inbounds double, double* %18, i64 2
  %20 = load double, double* %19, align 8
  %21 = load double*, double** %4, align 8
  %22 = getelementptr inbounds double, double* %21, i64 1
  %23 = load double, double* %22, align 8
  %24 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 6)
  %25 = call double %24(double %20, double %23)
  %26 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 5)
  %27 = call double %26(double %17, double %25)
  store double %27, double* %7, align 8
  %28 = load double*, double** %5, align 8
  %29 = getelementptr inbounds double, double* %28, i64 0
  %30 = load double, double* %29, align 8
  %31 = load double*, double** %4, align 8
  %32 = getelementptr inbounds double, double* %31, i64 3
  %33 = load double, double* %32, align 8
  %34 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 6)
  %35 = call double %34(double %30, double %33)
  %36 = load double*, double** %5, align 8
  %37 = getelementptr inbounds double, double* %36, i64 1
  %38 = load double, double* %37, align 8
  %39 = load double*, double** %4, align 8
  %40 = getelementptr inbounds double, double* %39, i64 1
  %41 = load double, double* %40, align 8
  %42 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 6)
  %43 = call double %42(double %38, double %41)
  %44 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 5)
  %45 = call double %44(double %35, double %43)
  store double %45, double* %8, align 8
  %46 = load double*, double** %4, align 8
  %47 = getelementptr inbounds double, double* %46, i64 0
  %48 = load double, double* %47, align 8
  %49 = load double*, double** %5, align 8
  %50 = getelementptr inbounds double, double* %49, i64 1
  %51 = load double, double* %50, align 8
  %52 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 6)
  %53 = call double %52(double %48, double %51)
  %54 = load double*, double** %4, align 8
  %55 = getelementptr inbounds double, double* %54, i64 2
  %56 = load double, double* %55, align 8
  %57 = load double*, double** %5, align 8
  %58 = getelementptr inbounds double, double* %57, i64 0
  %59 = load double, double* %58, align 8
  %60 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 6)
  %61 = call double %60(double %56, double %59)
  %62 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 5)
  %63 = call double %62(double %53, double %61)
  store double %63, double* %9, align 8
  %64 = load double, double* %8, align 8
  %65 = load double, double* %7, align 8
  %66 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 7)
  %67 = call double %66(double %64, double %65)
  %68 = load double*, double** %6, align 8
  %69 = getelementptr inbounds double, double* %68, i64 0
  store double %67, double* %69, align 8
  %70 = load double, double* %9, align 8
  %71 = load double, double* %7, align 8
  %72 = load double (double, double)*, double (double, double)** getelementptr inbounds ({ float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }, { float (float, float)*, float (float, float)*, float (float, float)*, float (float, float)*, double (double, double)*, double (double, double)*, double (double, double)*, double (double, double)* }* @_vfc_current_mca_interface, i32 0, i32 7)
  %73 = call double %72(double %70, double %71)
  %74 = load double*, double** %6, align 8
  %75 = getelementptr inbounds double, double* %74, i64 1
  store double %73, double* %75, align 8
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
