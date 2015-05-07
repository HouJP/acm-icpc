/*************************************************************************
    > File Name: Main.java
    > Author: HouJP
    > Mail: houjp1992@gmail.com
    > Created Time: 三  5/ 6 23:21:15 2015
 ************************************************************************/

/*
 * 第一次写java大数，这题从昨天到现在总共交了28发，终于在第28发过了，必须吐槽一下。
 *
 * 一看题目给列了好大一个公式，顿时有点慌，先去百度了一下，看看是不是用了什么我不知道的数学定理（免得浪费时间），然后有个家伙在博客里写到中国剩余定理，我就在想，果然不会，先去吭哧吭哧学了扩展欧几里得、中国剩余定理。
 * 回来一想，娘的，不对啊，根本用不上，dfs不就搞定了么。好，开始写，写完MLE，难道不能递归？然后改成DP，妈的，WA了。找啊找啊找啊，死活找不到问题在哪，然后把MAXN从100改成102，终于不WA了！！尼玛啊，说好的10^100呢？！！
 * 但是没有AC，又回到MLE，我晕，网上扒下来一个代码，用10W组case diff，没有错啊，难道又是递归？于是把f函数也从递归改成了非递归写法，果然，没有MLE了。到这里我的心已经稀碎，100层的递归啊，java怎么都吃不消！！！
 * 但是又WA了！！！好吧，继续diff，发现g函数没有错，f函数出问题了，一步步排查，终于找到：BitInteger对于负数取模之后竟然是非负的！！！毁三观啊！！！！卧槽！！！
 * 终于AC了！！！！！
 *
 * */

import java.io.FileInputStream;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	static BigInteger fortyfive = BigInteger.valueOf(45);
	static BigInteger ten = BigInteger.valueOf(10);
	static BigInteger nine = BigInteger.valueOf(9);
	static BigInteger two = BigInteger.valueOf(2);
	static BigInteger one = BigInteger.valueOf(1);
	static BigInteger zero = BigInteger.valueOf(0);
	
	static int MAXN = 102;
	static BigInteger l, r;
	static BigInteger ans, fans;
	static BigInteger tpow[] = new BigInteger[MAXN + 5];
	static BigInteger dpfull[] = new BigInteger[MAXN + 5];
	
	static void init() {
		tpow[0] = one;
		for (int i = 1; i <= MAXN; ++i) {
			tpow[i] = tpow[i - 1].multiply(ten);
		}
		
		for (int i = 0; i <= MAXN; ++i) {
			dpfull[i] = fortyfive.multiply(tpow[i]);
			if (1 == (i % 2)) {
				dpfull[i] = dpfull[i].subtract(fortyfive.multiply(tpow[i - 1]).multiply(nine));
			}
			if (0 != i) {
				dpfull[i] = dpfull[i].add(dpfull[i - 1]);
			}
		}
	}
	
	static BigInteger dp_f(BigInteger num) {
		BigInteger ret = zero;
		
		int len = num.toString().length();
		for (int i = 0; i < len - 1; ++i) {
			BigInteger h = num.mod(tpow[i + 1]).divide(tpow[i]);
			ret = ret.subtract(ret.multiply(two)); // h 之后的
			ret = ret.add(h.multiply(h.subtract(one)).divide(two).multiply(tpow[i])); // 0 ~ h-1
			if (1 == (i % 2)) {
				ret = ret.subtract(h.multiply(fortyfive.multiply(tpow[i - 1]))); // 0 ~ h-1 之后的
			}
			ret = ret.add(h.multiply(num.mod(tpow[i]).add(one))); // h
		}
		
		BigInteger h = num.divide(tpow[len - 1]);
		ret = ret.subtract(ret.multiply(two)); // h 之后
		ret = ret.add(h.multiply(num.mod(tpow[len - 1]).add(one))); // h
		if (1 == ((len - 1) % 2)) {
			ret = ret.subtract(h.subtract(one).multiply(fortyfive).multiply(tpow[len - 2])); // 1 ~ h-1之后
		}
		ret = ret.add(h.multiply(h.subtract(one)).divide(two).multiply(tpow[len - 1])); // 1 ~ h-1
		if (1 != len) {
			ret = ret.add(dpfull[len - 2]);
		}
		
		return ret;
	}
	
	public static void get_f() {
		if (zero.equals(fans)) {
			return;
		}
		fans = fans.mod(nine);
		if (zero.equals(fans)) {
			fans = nine;
			return;
		} 
	}
	
	public static void main(String[] args) {
		try {
			FileInputStream fis=new FileInputStream("data");  
			System.setIn(fis);
		} catch (Exception e) {
			
		}
		
		init();
		
		Scanner in = new Scanner(System.in);
		int t;
		t = in.nextInt();
		
		for (int i = 0; i < t; ++i) {
			l = in.nextBigInteger();
			r = in.nextBigInteger();
			if (!zero.equals(l)) {
				ans = dp_f(r).subtract(dp_f(l.subtract(one)));
			} else {
				ans = dp_f(r);
			}
			
			fans = ans;
			get_f();
			
			if (zero.equals(fans)) {
				System.out.println("Error!");
			} else {
				System.out.println(ans.mod(fans).add(fans).mod(fans));
			}
			
		}
	}
}
