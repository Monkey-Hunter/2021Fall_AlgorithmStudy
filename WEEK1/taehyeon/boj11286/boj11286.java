package taehyeon.boj11286;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.*;

class PQ implements Comparable<PQ>{
    int data;
    int sign;

    public PQ(){

    }

    public PQ(int data, int sign){
        this.data = data;
        this.sign = sign;
    }

    @Override
    public int compareTo(PQ target){

        if(this.data > target.data)
            return 1;
            
        else if(this.data == target.data)
            if(this.sign > target.sign)
                return 1;
            else
                return -1;
        else
            return -1;
    }
}

public class boj11286 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PriorityQueue<PQ> heap = new PriorityQueue<>();
        PQ output = new PQ();
        int N, x;

        N = Integer.parseInt(br.readLine());

        for(int i=0; i<N; i++){
            x = Integer.parseInt(br.readLine());

            if(x==0){
                if(!heap.isEmpty()){
                    output = heap.poll();
                    System.out.println(output.data*output.sign);
                }
                else
                    System.out.println(0);
                
            }

            else if(x>0)
                heap.offer(new PQ(x, 1));
            
            else   //(x<0)
                heap.offer(new PQ(-x, -1));

        }
    }
}