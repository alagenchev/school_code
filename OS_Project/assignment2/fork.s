; ModuleID = 'fork.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"pipe error\00", align 1
@.str1 = private unnamed_addr constant [11 x i8] c"fork error\00", align 1
@.str2 = private unnamed_addr constant [13 x i8] c"hello world\0A\00", align 1

define i32 @main() nounwind uwtable {
  %1 = alloca i32, align 4
  %n = alloca i32, align 4
  %fd = alloca [2 x i32], align 4
  %pid = alloca i32, align 4
  %line = alloca [4096 x i8], align 16
  store i32 0, i32* %1
  %2 = getelementptr inbounds [2 x i32]* %fd, i32 0, i32 0
  %3 = call i32 @pipe(i32* %2) nounwind
  %4 = icmp slt i32 %3, 0
  br i1 %4, label %5, label %6

; <label>:5                                       ; preds = %0
  call void (i8*, ...)* @err_sys(i8* getelementptr inbounds ([11 x i8]* @.str, i32 0, i32 0))
  br label %6

; <label>:6                                       ; preds = %5, %0
  %7 = call i32 @fork() nounwind
  store i32 %7, i32* %pid, align 4
  %8 = icmp slt i32 %7, 0
  br i1 %8, label %9, label %10

; <label>:9                                       ; preds = %6
  call void (i8*, ...)* @err_sys(i8* getelementptr inbounds ([11 x i8]* @.str1, i32 0, i32 0))
  br label %34

; <label>:10                                      ; preds = %6
  %11 = load i32* %pid, align 4
  %12 = icmp sgt i32 %11, 0
  br i1 %12, label %13, label %20

; <label>:13                                      ; preds = %10
  %14 = getelementptr inbounds [2 x i32]* %fd, i32 0, i64 0
  %15 = load i32* %14, align 4
  %16 = call i32 @close(i32 %15)
  %17 = getelementptr inbounds [2 x i32]* %fd, i32 0, i64 1
  %18 = load i32* %17, align 4
  %19 = call i64 @write(i32 %18, i8* getelementptr inbounds ([13 x i8]* @.str2, i32 0, i32 0), i64 12)
  br label %33

; <label>:20                                      ; preds = %10
  %21 = getelementptr inbounds [2 x i32]* %fd, i32 0, i64 1
  %22 = load i32* %21, align 4
  %23 = call i32 @close(i32 %22)
  %24 = getelementptr inbounds [2 x i32]* %fd, i32 0, i64 0
  %25 = load i32* %24, align 4
  %26 = getelementptr inbounds [4096 x i8]* %line, i32 0, i32 0
  %27 = call i64 @read(i32 %25, i8* %26, i64 4096)
  %28 = trunc i64 %27 to i32
  store i32 %28, i32* %n, align 4
  %29 = getelementptr inbounds [4096 x i8]* %line, i32 0, i32 0
  %30 = load i32* %n, align 4
  %31 = sext i32 %30 to i64
  %32 = call i64 @write(i32 1, i8* %29, i64 %31)
  br label %33

; <label>:33                                      ; preds = %20, %13
  br label %34

; <label>:34                                      ; preds = %33, %9
  call void @exit(i32 0) noreturn nounwind
  unreachable
                                                  ; No predecessors!
  %36 = load i32* %1
  ret i32 %36
}

declare i32 @pipe(i32*) nounwind

declare void @err_sys(i8*, ...)

declare i32 @fork() nounwind

declare i32 @close(i32)

declare i64 @write(i32, i8*, i64)

declare i64 @read(i32, i8*, i64)

declare void @exit(i32) noreturn nounwind
