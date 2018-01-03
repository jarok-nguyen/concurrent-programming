package utils.speedup;

/*
 * Riferimento : https://en.wikipedia.org/wiki/Speedup#Using_execution_times
 */

import adder.BinaryTreeAdder;
import adder.BinaryTreeAdderThreads;
import adder.Hwj1;
import tree.Tree;
import tree.TreeNode;

public class PerformanceCalculator {
    private static int NCPU = Runtime.getRuntime().availableProcessors();
    private long startTime;
    private long stopTime;

    public PerformanceCalculator() {
        this.startTime = 0;
        this.stopTime = 0;
    }

    public long startTime() {
        this.startTime = System.nanoTime();
        return this.startTime;
    }

    public long stopTime() {
        this.stopTime = System.nanoTime();
        return this.stopTime;
    }

    public long getElapsedTime() {
        return this.stopTime - this.startTime;
    }

    public long getSpeedUp(long oldElapsedTime, long newElapsedTime) {
        long speedup = oldElapsedTime / newElapsedTime;
        return speedup;
    }

    public void speedUpComputation(BinaryTreeAdderThreads adder, int treeDepth) {
        //int depth = 3;
        //Hwj1 tmp = new Hwj1("HWJ1");
        TreeNode rootNode = (TreeNode) new Tree().generateBinaryTree(treeDepth);

        PerformanceCalculator serialePc = new PerformanceCalculator();
        adder.setNThreads(1);
        serialePc.startTime();
        int serialeResult = adder.computeOnerousSum(rootNode); // (2^(depth+1))-1
        serialePc.stopTime();
        long serialeElapsedTime = serialePc.getElapsedTime();

        PerformanceCalculator concorrentePc = new PerformanceCalculator();
        adder.setNThreads(NCPU);
        concorrentePc.startTime();
        int concorrenteResult = adder.computeOnerousSum(rootNode); //(2^(depth+1))-1
        concorrentePc.stopTime();
        long concorrenteElapsedTime = concorrentePc.getElapsedTime();

        long speedup = new PerformanceCalculator().getSpeedUp(serialeElapsedTime, concorrenteElapsedTime);

        System.out.print("["+ adder.getName() +"] tree depth " + treeDepth +
                ", seriale (1 Thread) " + serialeElapsedTime / 1000000000.0 +
                "s, concorrente ("+ NCPU +" Thread) " + concorrenteElapsedTime / 1000000000.0 +
                "s, speedup: " + speedup);
    }
}

