; ModuleID = 'kahan.c'
source_filename = "kahan.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@.str = private unnamed_addr constant [16 x i8] c"rSumKahan > 0.0\00", align 1
@.str.1 = private unnamed_addr constant [8 x i8] c"kahan.c\00", align 1
@__PRETTY_FUNCTION__.show_sums = private unnamed_addr constant [35 x i8] c"void show_sums(const float *, int)\00", align 1
@.str.2 = private unnamed_addr constant [14 x i8] c"Kahan = %.7e\0A\00", align 1
@stderr = external local_unnamed_addr global %struct._IO_FILE*, align 8
@.str.4 = private unnamed_addr constant [23 x i8] c"Usage: %s array-size.\0A\00", align 1
@.str.5 = private unnamed_addr constant [30 x i8] c"Array size must be positive.\0A\00", align 1
@.str.6 = private unnamed_addr constant [23 x i8] c"Compile-time options: \00", align 1
@.str.7 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.9 = private unnamed_addr constant [26 x i8] c"Random number seed = %i.\0A\00", align 1
@.str.10 = private unnamed_addr constant [25 x i8] c"Input: array size = %i.\0A\00", align 1
@str = private unnamed_addr constant [27 x i8] c"Kahan summation algorithm.\00"
@str.11 = private unnamed_addr constant [2 x i8] c".\00"

; Function Attrs: noinline norecurse nounwind readonly uwtable
define float @sum_kahan(float* nocapture readonly, i32) local_unnamed_addr #0 {
  %3 = load float, float* %0, align 4, !tbaa !1
  %4 = icmp sgt i32 %1, 1
  br i1 %4, label %5, label %115

; <label>:5:                                      ; preds = %2
  %6 = zext i32 %1 to i64
  %7 = add nsw i64 %6, -1
  %8 = icmp ult i64 %7, 8
  br i1 %8, label %103, label %9

; <label>:9:                                      ; preds = %5
  %10 = and i64 %7, -8
  %11 = icmp eq i64 %10, 0
  %12 = or i64 %10, 1
  br i1 %11, label %103, label %13

; <label>:13:                                     ; preds = %9
  %14 = insertelement <4 x float> <float undef, float 0.000000e+00, float 0.000000e+00, float 0.000000e+00>, float %3, i32 0
  %15 = add nsw i64 %10, -8
  %16 = lshr exact i64 %15, 3
  %17 = add nuw nsw i64 %16, 1
  %18 = and i64 %17, 3
  %19 = icmp eq i64 %18, 0
  br i1 %19, label %39, label %20

; <label>:20:                                     ; preds = %13
  br label %21

; <label>:21:                                     ; preds = %21, %20
  %22 = phi i64 [ 0, %20 ], [ %35, %21 ]
  %23 = phi <4 x float> [ %14, %20 ], [ %33, %21 ]
  %24 = phi <4 x float> [ zeroinitializer, %20 ], [ %34, %21 ]
  %25 = phi i64 [ %18, %20 ], [ %36, %21 ]
  %26 = or i64 %22, 1
  %27 = getelementptr inbounds float, float* %0, i64 %26
  %28 = bitcast float* %27 to <4 x float>*
  %29 = load <4 x float>, <4 x float>* %28, align 4, !tbaa !1
  %30 = getelementptr float, float* %27, i64 4
  %31 = bitcast float* %30 to <4 x float>*
  %32 = load <4 x float>, <4 x float>* %31, align 4, !tbaa !1
  %33 = fadd fast <4 x float> %29, %23
  %34 = fadd fast <4 x float> %32, %24
  %35 = add i64 %22, 8
  %36 = add i64 %25, -1
  %37 = icmp eq i64 %36, 0
  br i1 %37, label %38, label %21, !llvm.loop !5

; <label>:38:                                     ; preds = %21
  br label %39

; <label>:39:                                     ; preds = %13, %38
  %40 = phi <4 x float> [ undef, %13 ], [ %33, %38 ]
  %41 = phi <4 x float> [ undef, %13 ], [ %34, %38 ]
  %42 = phi i64 [ 0, %13 ], [ %35, %38 ]
  %43 = phi <4 x float> [ %14, %13 ], [ %33, %38 ]
  %44 = phi <4 x float> [ zeroinitializer, %13 ], [ %34, %38 ]
  %45 = icmp ult i64 %15, 24
  br i1 %45, label %93, label %46

; <label>:46:                                     ; preds = %39
  br label %47

; <label>:47:                                     ; preds = %47, %46
  %48 = phi i64 [ %42, %46 ], [ %90, %47 ]
  %49 = phi <4 x float> [ %43, %46 ], [ %88, %47 ]
  %50 = phi <4 x float> [ %44, %46 ], [ %89, %47 ]
  %51 = or i64 %48, 1
  %52 = getelementptr inbounds float, float* %0, i64 %51
  %53 = bitcast float* %52 to <4 x float>*
  %54 = load <4 x float>, <4 x float>* %53, align 4, !tbaa !1
  %55 = getelementptr float, float* %52, i64 4
  %56 = bitcast float* %55 to <4 x float>*
  %57 = load <4 x float>, <4 x float>* %56, align 4, !tbaa !1
  %58 = fadd fast <4 x float> %54, %49
  %59 = fadd fast <4 x float> %57, %50
  %60 = add i64 %48, 8
  %61 = or i64 %60, 1
  %62 = getelementptr inbounds float, float* %0, i64 %61
  %63 = bitcast float* %62 to <4 x float>*
  %64 = load <4 x float>, <4 x float>* %63, align 4, !tbaa !1
  %65 = getelementptr float, float* %62, i64 4
  %66 = bitcast float* %65 to <4 x float>*
  %67 = load <4 x float>, <4 x float>* %66, align 4, !tbaa !1
  %68 = fadd fast <4 x float> %64, %58
  %69 = fadd fast <4 x float> %67, %59
  %70 = add i64 %48, 16
  %71 = or i64 %70, 1
  %72 = getelementptr inbounds float, float* %0, i64 %71
  %73 = bitcast float* %72 to <4 x float>*
  %74 = load <4 x float>, <4 x float>* %73, align 4, !tbaa !1
  %75 = getelementptr float, float* %72, i64 4
  %76 = bitcast float* %75 to <4 x float>*
  %77 = load <4 x float>, <4 x float>* %76, align 4, !tbaa !1
  %78 = fadd fast <4 x float> %74, %68
  %79 = fadd fast <4 x float> %77, %69
  %80 = add i64 %48, 24
  %81 = or i64 %80, 1
  %82 = getelementptr inbounds float, float* %0, i64 %81
  %83 = bitcast float* %82 to <4 x float>*
  %84 = load <4 x float>, <4 x float>* %83, align 4, !tbaa !1
  %85 = getelementptr float, float* %82, i64 4
  %86 = bitcast float* %85 to <4 x float>*
  %87 = load <4 x float>, <4 x float>* %86, align 4, !tbaa !1
  %88 = fadd fast <4 x float> %84, %78
  %89 = fadd fast <4 x float> %87, %79
  %90 = add i64 %48, 32
  %91 = icmp eq i64 %90, %10
  br i1 %91, label %92, label %47, !llvm.loop !7

; <label>:92:                                     ; preds = %47
  br label %93

; <label>:93:                                     ; preds = %39, %92
  %94 = phi <4 x float> [ %40, %39 ], [ %88, %92 ]
  %95 = phi <4 x float> [ %41, %39 ], [ %89, %92 ]
  %96 = fadd fast <4 x float> %95, %94
  %97 = shufflevector <4 x float> %96, <4 x float> undef, <4 x i32> <i32 2, i32 3, i32 undef, i32 undef>
  %98 = fadd fast <4 x float> %96, %97
  %99 = shufflevector <4 x float> %98, <4 x float> undef, <4 x i32> <i32 1, i32 undef, i32 undef, i32 undef>
  %100 = fadd fast <4 x float> %98, %99
  %101 = extractelement <4 x float> %100, i32 0
  %102 = icmp eq i64 %7, %10
  br i1 %102, label %115, label %103

; <label>:103:                                    ; preds = %93, %9, %5
  %104 = phi i64 [ 1, %9 ], [ 1, %5 ], [ %12, %93 ]
  %105 = phi float [ %3, %9 ], [ %3, %5 ], [ %101, %93 ]
  br label %106

; <label>:106:                                    ; preds = %103, %106
  %107 = phi i64 [ %112, %106 ], [ %104, %103 ]
  %108 = phi float [ %111, %106 ], [ %105, %103 ]
  %109 = getelementptr inbounds float, float* %0, i64 %107
  %110 = load float, float* %109, align 4, !tbaa !1
  %111 = fadd fast float %110, %108
  %112 = add nuw nsw i64 %107, 1
  %113 = icmp eq i64 %112, %6
  br i1 %113, label %114, label %106, !llvm.loop !10

; <label>:114:                                    ; preds = %106
  br label %115

; <label>:115:                                    ; preds = %114, %93, %2
  %116 = phi float [ %3, %2 ], [ %101, %93 ], [ %111, %114 ]
  ret float %116
}

; Function Attrs: nounwind uwtable
define void @fill_array(float* nocapture, i32) local_unnamed_addr #1 {
  %3 = icmp sgt i32 %1, 0
  br i1 %3, label %4, label %15

; <label>:4:                                      ; preds = %2
  %5 = zext i32 %1 to i64
  br label %6

; <label>:6:                                      ; preds = %4, %6
  %7 = phi i64 [ %12, %6 ], [ 0, %4 ]
  %8 = tail call i32 @rand() #4
  %9 = sitofp i32 %8 to float
  %10 = fmul fast float %9, 0x3E00000000000000
  %11 = getelementptr inbounds float, float* %0, i64 %7
  store float %10, float* %11, align 4, !tbaa !1
  %12 = add nuw nsw i64 %7, 1
  %13 = icmp eq i64 %12, %5
  br i1 %13, label %14, label %6

; <label>:14:                                     ; preds = %6
  br label %15

; <label>:15:                                     ; preds = %14, %2
  ret void
}

; Function Attrs: nounwind
declare i32 @rand() local_unnamed_addr #2

; Function Attrs: nounwind uwtable
define void @show_sums(float* nocapture readonly, i32) local_unnamed_addr #1 {
  %3 = tail call fast float @sum_kahan(float* %0, i32 %1)
  %4 = fcmp ogt float %3, 0.000000e+00
  br i1 %4, label %6, label %5

; <label>:5:                                      ; preds = %2
  tail call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 65, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.show_sums, i64 0, i64 0)) #5
  unreachable

; <label>:6:                                      ; preds = %2
  %7 = fpext float %3 to double
  %8 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i64 0, i64 0), double %7)
  ret void
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) local_unnamed_addr #3

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #2

; Function Attrs: nounwind uwtable
define i32 @main(i32, i8** nocapture readonly) local_unnamed_addr #1 {
  %3 = tail call i32 @puts(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @str, i64 0, i64 0))
  %4 = icmp eq i32 %0, 2
  br i1 %4, label %9, label %5

; <label>:5:                                      ; preds = %2
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !12
  %7 = load i8*, i8** %1, align 8, !tbaa !12
  %8 = tail call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %6, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i64 0, i64 0), i8* %7) #6
  br label %42

; <label>:9:                                      ; preds = %2
  %10 = getelementptr inbounds i8*, i8** %1, i64 1
  %11 = load i8*, i8** %10, align 8, !tbaa !12
  %12 = tail call i64 @strtol(i8* nocapture nonnull %11, i8** null, i32 10) #4
  %13 = trunc i64 %12 to i32
  %14 = icmp slt i32 %13, 1
  br i1 %14, label %15, label %18

; <label>:15:                                     ; preds = %9
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !tbaa !12
  %17 = tail call i64 @fwrite(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.5, i64 0, i64 0), i64 29, i64 1, %struct._IO_FILE* %16) #6
  br label %42

; <label>:18:                                     ; preds = %9
  %19 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.6, i64 0, i64 0))
  %20 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i64 0, i64 0))
  %21 = tail call i32 @puts(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @str.11, i64 0, i64 0))
  tail call void @srand(i32 0) #4
  %22 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.9, i64 0, i64 0), i32 0)
  %23 = and i64 %12, 4294967295
  %24 = tail call i8* @llvm.stacksave()
  %25 = alloca float, i64 %23, align 16
  %26 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.10, i64 0, i64 0), i32 %13)
  br label %27

; <label>:27:                                     ; preds = %27, %18
  %28 = phi i64 [ %33, %27 ], [ 0, %18 ]
  %29 = tail call i32 @rand() #4
  %30 = sitofp i32 %29 to float
  %31 = fmul fast float %30, 0x3E00000000000000
  %32 = getelementptr inbounds float, float* %25, i64 %28
  store float %31, float* %32, align 4, !tbaa !1
  %33 = add nuw nsw i64 %28, 1
  %34 = icmp eq i64 %33, %23
  br i1 %34, label %35, label %27

; <label>:35:                                     ; preds = %27
  %36 = call fast float @sum_kahan(float* nonnull %25, i32 %13) #4
  %37 = fcmp ogt float %36, 0.000000e+00
  br i1 %37, label %39, label %38

; <label>:38:                                     ; preds = %35
  tail call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 65, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @__PRETTY_FUNCTION__.show_sums, i64 0, i64 0)) #5
  unreachable

; <label>:39:                                     ; preds = %35
  %40 = fpext float %36 to double
  %41 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i64 0, i64 0), double %40) #4
  tail call void @llvm.stackrestore(i8* %24)
  br label %42

; <label>:42:                                     ; preds = %15, %39, %5
  %43 = phi i32 [ 1, %5 ], [ 1, %15 ], [ 0, %39 ]
  ret i32 %43
}

; Function Attrs: nounwind
declare i32 @fprintf(%struct._IO_FILE* nocapture, i8* nocapture readonly, ...) local_unnamed_addr #2

; Function Attrs: nounwind
declare void @srand(i32) local_unnamed_addr #2

; Function Attrs: nounwind
declare i8* @llvm.stacksave() #4

; Function Attrs: nounwind
declare void @llvm.stackrestore(i8*) #4

; Function Attrs: nounwind
declare i64 @strtol(i8* readonly, i8** nocapture, i32) local_unnamed_addr #2

; Function Attrs: nounwind
declare i32 @puts(i8* nocapture readonly) #4

; Function Attrs: nounwind
declare i64 @fwrite(i8* nocapture, i64, i64, %struct._IO_FILE* nocapture) #4

attributes #0 = { noinline norecurse nounwind readonly uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="true" "no-jump-tables"="false" "no-nans-fp-math"="true" "no-signed-zeros-fp-math"="true" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="true" "use-soft-float"="false" }
attributes #1 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="true" "no-jump-tables"="false" "no-nans-fp-math"="true" "no-signed-zeros-fp-math"="true" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="true" "use-soft-float"="false" }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="true" "no-nans-fp-math"="true" "no-signed-zeros-fp-math"="true" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="true" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="true" "no-nans-fp-math"="true" "no-signed-zeros-fp-math"="true" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="true" "use-soft-float"="false" }
attributes #4 = { nounwind }
attributes #5 = { noreturn nounwind }
attributes #6 = { cold }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.1-10 (tags/RELEASE_401/final)"}
!1 = !{!2, !2, i64 0}
!2 = !{!"float", !3, i64 0}
!3 = !{!"omnipotent char", !4, i64 0}
!4 = !{!"Simple C/C++ TBAA"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.unroll.disable"}
!7 = distinct !{!7, !8, !9}
!8 = !{!"llvm.loop.vectorize.width", i32 1}
!9 = !{!"llvm.loop.interleave.count", i32 1}
!10 = distinct !{!10, !11, !8, !9}
!11 = !{!"llvm.loop.unroll.runtime.disable"}
!12 = !{!13, !13, i64 0}
!13 = !{!"any pointer", !3, i64 0}
