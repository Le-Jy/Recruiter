package fr.epita.assistants.scheduler;

import java.util.ArrayList;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.function.Function;
import java.util.function.Supplier;

public class MyTask<INPUT_TYPE, RETURN_TYPE> implements Task<RETURN_TYPE> {

    public MyTask(CompletableFuture<RETURN_TYPE> currentTask) {
        this.currentTask = currentTask;
    }

    CompletableFuture<RETURN_TYPE> currentTask;

    static <RETURN_TYPE> Task<RETURN_TYPE> of(Supplier<RETURN_TYPE> actionSupplier) {
        CompletableFuture<RETURN_TYPE> task = CompletableFuture.supplyAsync(actionSupplier);
        return new MyTask<>(task);
    }

    @Override
    public CompletableFuture<RETURN_TYPE> build() {
        return this.currentTask;
    }

    @Override
    public Task<RETURN_TYPE> onErrorRecoverWith(Function<Throwable, RETURN_TYPE> recoveryFunction) {
        return new MyTask<>(this.currentTask.exceptionally(recoveryFunction));
    }

    @Override
    public <NEW_RETURN_TYPE> Task<NEW_RETURN_TYPE> andThenDo(Function<RETURN_TYPE, NEW_RETURN_TYPE> action) {
        return new MyTask<>(this.currentTask.thenApply(action));
    }

    @Override
    public Task<RETURN_TYPE> andThenWait(long number, TimeUnit timeUnit) {
        return new MyTask<>(this.currentTask.thenCompose(C ->
                CompletableFuture.supplyAsync(() -> C, CompletableFuture.delayedExecutor(number, timeUnit))));
    }
}
