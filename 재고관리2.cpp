#include <stdio.h>
#include <stdlib.h>

int main()
{
    int product_number; // ��ǰ ���� ���� 

    // 1. ��ǰ ���� �Է�
    printf("��ǰ�� ���� ������ �Է��ϼ��� (1 ~ 100): ");
    scanf("%d", &product_number);

    int product_stock_income[101] = { 0 };   // �԰� ����
    int product_stock_sold[101] = { 0 };     // �Ǹ� ����
    int product_stock_current[101] = { 0 };  // ��� ����

    // 2. �԰� ���� �Է�
    printf("\n�� ��ǰ�� �԰� ������ �Է��ϼ���.\n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("��ǰ ID %d �԰� ����: ", i);
        scanf("%d", &product_stock_income[i]);

        // �ʱ� ��� = �԰� ����
        product_stock_current[i] = product_stock_income[i];
    }

    // 3. �Ǹ� ���� �Է�
    printf("\n�� ��ǰ�� �Ǹ� ������ �Է��ϼ���.\n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("��ǰ ID %d �Ǹ� ����: ", i);
        scanf("%d", &product_stock_sold[i]);

        // ��� ���
        product_stock_current[i] -= product_stock_sold[i];
        if (product_stock_current[i] < 0) product_stock_current[i] = 0; // ���� ����
    }

    // 4. ��� ��ǰ�� ��� ���� ���
    printf("\n ----- ��ǰ�� ��� ��Ȳ ----- \n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("��ǰ ID %d - ��� : %d��\n", i, product_stock_current[i]);
    }

    // 5. ��ü �Ǹŷ� ���
    int total_sold = 0, total_income = 0; // ��ü �Ǹŷ�
    for (int i = 1; i <= product_number; i++)
    {
        total_sold += product_stock_sold[i];
        total_income += product_stock_income[i];
    }
    printf("\n��ü �Ǹŷ�: %d��\n", total_sold);

    // 6. ��ü �Ǹ��� ���
    double sales_rate = 0; // �Ǹ�
    if (total_income > 0)
        sales_rate = (double)total_sold / total_income * 100;
    printf("��ü �Ǹ���: %.2f%%\n", sales_rate);

    // 7. �ִ�/�ּ� �Ǹŷ� ��ǰ
    int max_sold = product_stock_sold[1], min_sold = product_stock_sold[1];
    int max_id = 1, min_id = 1;

    for (int i = 2; i <= product_number; i++)
    {
        if (product_stock_sold[i] > max_sold)
        {
            max_sold = product_stock_sold[i];
            max_id = i;
        }
        if (product_stock_sold[i] < min_sold)
        {
            min_sold = product_stock_sold[i];
            min_id = i;
        }
    }

    printf("�ִ� �Ǹŷ� ��ǰ: ID %d (�Ǹ� %d��)\n", max_id, max_sold);
    printf("�ּ� �Ǹŷ� ��ǰ: ID %d (�Ǹ� %d��)\n", min_id, min_sold);

    // 8. ��� ���� ���
    printf("\n===== ��� ���� ��� =====\n");
    int warning_count = 0;
    for (int i = 1; i <= product_number; i++)
    {
        if (product_stock_current[i] <= 2)
        {
            printf("?? ��ǰ ID %d�� ��� �����մϴ�! (���: %d��)\n", i, product_stock_current[i]);
            warning_count++;
        }
    }
    if (warning_count == 0)
        printf("��� ��ǰ�� ��� ����մϴ�.\n");

    return 0;
}
