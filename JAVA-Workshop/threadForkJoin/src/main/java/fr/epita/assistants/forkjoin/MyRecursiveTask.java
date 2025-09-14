package fr.epita.assistants.forkjoin;

import java.util.concurrent.RecursiveTask;

public class MyRecursiveTask extends RecursiveTask<Double> {
    final private double[][] matrix;
    final private int xLowerBound;
    final private int xUpperBound;
    final private int yLowerBound;
    final private int yUpperBound;

    public MyRecursiveTask(double[][] matrix, int xLowerBound, int xUpperBound, int yLowerBound, int yUpperBound) {
        this.matrix = matrix;
        this.xLowerBound = xLowerBound;
        this.xUpperBound = xUpperBound;
        this.yLowerBound = yLowerBound;
        this.yUpperBound = yUpperBound;
    }

    @Override
    protected Double compute() {
        if (this.matrix.length == 0)
            return (double) 0;
        double res = 0;
        if (this.xUpperBound - this.xLowerBound <= 5 && this.yUpperBound - this.yLowerBound <= 5) {
            int counter = 0;
            double sum = 0;
            for (int i = yLowerBound; i < yUpperBound; i++) {
                for (int j  = xLowerBound; j < xUpperBound; j++) {
                    sum = sum + this.matrix[i][j];
                    counter++;
                }
            }
            res = sum / counter;
        }
        else {
            MyRecursiveTask[] averager = new MyRecursiveTask[4];
            var midx = (this.xLowerBound + this.xUpperBound) / 2;
            var midy = (this.yLowerBound + this.yUpperBound) / 2;
            averager[0] = new MyRecursiveTask(this.matrix, this.xLowerBound, midx, this.yLowerBound, midy); //left bot
            averager[1] = new MyRecursiveTask(this.matrix, this.xLowerBound, midx, midy , this.yUpperBound ); //left top
            averager[2] = new MyRecursiveTask(this.matrix, midx, this.xUpperBound, midy, this.yUpperBound); //right top
            averager[3] = new MyRecursiveTask(this.matrix, midx, this.xUpperBound, this.yLowerBound, midy); //right bot
            for (int i = 0; i < 4; i++) {
                averager[i].fork();
            }
            for (int i = 0; i < 4; i++) {
                res += averager[i].join();
            }
            res /= 4;
        }
        return res;
    }
}
