#include <stdio.h>
#include <stdlib.h>

int main()
{
    int product_number; // ��ǰ�� ���� ���� (1~100)

    // 1. ��ǰ ���� �Է�
    printf("��ǰ�� ���� ������ �Է��ϼ��� (1 ~ 100): ");
    scanf("%d", &product_number);

    int product_stock_income[101] = { 0 };  // �԰� ����
    int product_stock_sold[101] = { 0 };    // �Ǹ� ����
    int product_stock_current[101] = { 0 }; // ��� ����

    // 2. �԰� ���� �Է�
    printf("\n�� ��ǰ�� �԰� ������ �Է��ϼ���.\n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("��ǰ ID %d �԰� ����: ", i);
        scanf("%d", &product_stock_income[i]);

        // ���� ��� ���� ���ΰ�ħ
        product_stock_current[i] = product_stock_income[i];
    }

    // 3. �Ǹ� ���� �Է�
    printf("\n�� ��ǰ�� �Ǹ� ������ �Է��ϼ���.\n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("��ǰ ID %d �Ǹ� ����: ", i);
        scanf("%d", &product_stock_sold[i]);

        // ���� ��� ���� ���ΰ�ħ
        product_stock_current[i] -= product_stock_sold[i];
    }

    // 4. Ư�� ��ǰ ��� Ȯ��
    int specific_product_stock;
    printf("\n��� Ȯ���� ��ǰ�� ID�� �Է��ϼ��� (1 ~ %d): ", product_number);
    scanf("%d", &specific_product_stock);
    // Ư�� ��ǰ ��� ���
    printf("\n��ǰ ID %d�� ���� ���: %d��\n", specific_product_stock, product_stock_current[specific_product_stock]);

    // 5. ��ü ��� ���� Ȯ��
    int total_stock = 0;
    for (int i = 1; i <= product_number; i++)
    {
        total_stock += product_stock_current[i];
    }
    // ��ü ��� ���� ���
    printf("��ü ��� ����: %d��\n", total_stock);

    return 0;
}