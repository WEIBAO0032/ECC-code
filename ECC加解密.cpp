#include <bits/stdc++.h>
using namespace std;

// ��ʾ��Բ�����ϵĵ�
vector<pair<int, int>> show_points(int a, int b, int p) {
  			  vector<pair<int, int>> points;
  			  for (int x = 0; x < p; x++) {
        			for (int y = 0; y < p; y++) {
           			 if ((y * y) % p == (x * x * x + a * x + b) % p) {
             	   			 points.push_back({x, y});
          			 	}
      		  		}
   			 }
  			  return points;
}

// �������Լ��
int gcd(int x, int y) {
    return (y == 0) ? x : gcd(y, x % y);
}

// ����ģ��Ԫ
int get_inverse_element(int value, int mod) {
    value = (value % mod + mod) % mod;
    for (int i = 1; i < mod; i++) {
        if ((i * value) % mod == 1) {
            return i;
        }
    }
    throw runtime_error("No modular inverse found!");
}

// ���� P + Q
pair<int, int> calculate_P_Q(int x1, int y1, int x2, int y2, int a, int p) {
    int member, denominator, k;
    if (x1 == x2 && y1 == y2) { // �㱶��
        member = (3 * x1 * x1 + a) % p;
        denominator = (2 * y1) % p;
    } else { // ���
        member = (y2 - y1) % p;
        denominator = (x2 - x1) % p;
    }

    if (denominator == 0) {
        throw runtime_error("Denominator is zero. Points are not distinct or on the curve.");
    }

    int inverse_value = get_inverse_element(denominator, p);
    k = (member * inverse_value) % p;

    int x3 = (k * k - x1 - x2) % p;
    int y3 = (k * (x1 - x3) - y1) % p;

    if (x3 < 0) x3 += p;
    if (y3 < 0) y3 += p;

    return {x3, y3};
}

// �������Ľ�
int get_order(int x0, int y0, int a, int b, int p) {
    int x1 = x0;
    int y1 = (p - y0) % p;  // ȷ��Ϊ����

    int temp_x = x0;
    int temp_y = y0;
    int n = 1;

    while (true) {
        n += 1;
        auto G = calculate_P_Q(temp_x, temp_y, x0, y0, a, p);
        if (G.first == x1 && G.second == y1) {
            return n + 1;  // �ҵ��������
        }
        temp_x = G.first;
        temp_y = G.second;
    }
}

// ���� nP��ֵ 
pair<int, int> calculate_np(int x, int y, int n, int a, int p) {
    pair<int, int> result = {x, y};
    for (int i = 1; i < n; i++) {
        result = calculate_P_Q(result.first, result.second, x, y, a, p);
    }
    return result;
}

// �������������ļӽ��ܹ���
int main() {
    int a, b, p;
    while (true) {
        cout << "������Բ���߲��� a��b��p����������";
        cin >> a >> b >> p;
        if ((4 * a * a * a + 27 * b * b) % p == 0) {
            cout << "ѡ���� a, b, p ������Ҫ��������ѡ��" << endl;
        } else {
            break;
        }
    }

    vector<pair<int, int>> newpoint = show_points(a, b, p);
    for (auto &point : newpoint) {
        printf("(%d %d) ", point.first, point.second);
    }
    cout << endl;

    int G_x, G_y;
    cout << "����Ļ���Ϊ��";
    cin >> G_x >> G_y;

    int neworder = get_order(G_x, G_y, a, b, p);
    cout << "�����Ӧ�Ľ�Ϊ " << neworder << endl;

    int private_key;
    cout << "����˽Կ��С�� n����";
    cin >> private_key;
    pair<int, int> Q = calculate_np(G_x, G_y, private_key, a, p);
    cout << "��Կ Q(" << Q.first << ", " << Q.second << ")" << endl;

    int k;
    cout << "��������� k��С�� n����";
    cin >> k;
    pair<int, int> kG = calculate_np(G_x, G_y, k, a, p);
    pair<int, int> kQ = calculate_np(Q.first, Q.second, k, a, p);

    int plain_text;
    cout << "�������ģ�";
    cin >> plain_text;
    int cipher_text = (plain_text * kQ.first) % p;
    cout << "����Ϊ����" << kG.first << ", " << kG.second << "��, " << cipher_text << endl;

    pair<int, int> decrypto_text = calculate_np(kG.first, kG.second, private_key, a, p);
    int inverse_value = get_inverse_element(decrypto_text.first, p);
    int m = (cipher_text * inverse_value) % p;
    if (m < 0) m += p;
    cout << "���ܺ������Ϊ��" << m << endl;

    return 0;
}					

