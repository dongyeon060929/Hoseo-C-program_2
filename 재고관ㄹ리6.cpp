#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_NAME_LEN 50
#define DATA_FILE "products.dat"

typedef struct 
{
    char name[MAX_NAME_LEN];        // ��ǰ �̸�
    int stock_income;               // �� �԰�� ����
    int stock_sold;                 // �� �Ǹŵ� ����
    int stock_current;              // ���� �����ִ� ���
    int price;                      // �Ǹ� ����
    long long total_revenue;        // �� ��ǰ���� ������� �� ���� �ݾ�
} Product;

// --- 1. �Լ� ����
void clear_input_buffer();
void save_data(Product products[], int count);
void load_data(Product products[], int count); 
void handle_income(Product products[], int count); // 1. �԰� ó��
void handle_sale(Product products[], int count);   // 2. �Ǹ� ó��
void handle_individual_info(Product products[], int count); // 3. ���� ��ǰ ���� ��ȸ/����
void handle_overall_status(Product products[], int count);  // 4. ��ü ��Ȳ ��ȸ

// --- 2. ���� �Լ�
int main() {
    int menu;
    Product products[MAX_PRODUCTS + 1] = { 0 };

    for (int i = 1; i <= MAX_PRODUCTS; i++) 
    {
        strcpy(products[i].name, "(���Է�)");
    }

    printf("? ���θ� ��� ���� ���α׷� ���� ?\n");

    while (1) 
    { 
        printf("\n1. �԰�\n2. �Ǹ�\n3. ������ǰ����\n4. ��ü��Ȳ\n5. ��ǰ����\n6. ��ǰ�ҷ�����\n7. ����\n����: ");

        if (scanf("%d", &menu) != 1) 
        {
            printf("���ڷθ� �Է����ּ���.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (menu) 
        {
        case 1: handle_income(products, MAX_PRODUCTS); break;
        case 2: handle_sale(products, MAX_PRODUCTS); break;
        case 3: handle_individual_info(products, MAX_PRODUCTS); break;
        case 4: handle_overall_status(products, MAX_PRODUCTS); break;
        case 5: save_data(products, MAX_PRODUCTS); break;      
        case 6: load_data(products, MAX_PRODUCTS); break;     
        case 7: printf("���α׷��� �����մϴ�.\n"); return 0; 
        default: printf("1���� 7 �� �ϳ��� �����ϼ���.\n"); break;
        }
    }
}

// --- 3. �� ��� ���� �Լ� ---

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// (1) �԰� ó�� �Լ�
void handle_income(Product products[], int count)
{
    int id, quantity, price;
    printf("\n<< 1. �԰� >>\n��ǰ ID (1~%d): ", count);
    if (scanf("%d", &id) != 1 || id < 1 || id > count)
    {
        printf("�߸��� ��ǰ ��ȣ�Դϴ�.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    // ��ǰ���� ������ ���� �Է�
    if (strcmp(products[id].name, "(���Է�)") == 0)
    {
        printf("��ǰ�� �Է�: ");
        if (fgets(products[id].name, MAX_NAME_LEN, stdin) != NULL)
            products[id].name[strcspn(products[id].name, "\n")] = 0;
    }
    else 
    {
        printf("��ǰ��: %s\n", products[id].name);
    }

    // �԰� ���� �� ������ �Է¹ް� ��ȿ�� �˻�
    printf("�԰� ����: ");
    if (scanf("%d", &quantity) != 1 || quantity <= 0) 
    {
        printf("������ 1�� �̻��̾�� �մϴ�.\n"); clear_input_buffer(); return;
    }
    printf("�Ǹ� ����: ");
    if (scanf("%d", &price) != 1 || price < 0)
    {
        printf("������ 0�� �̻��̾�� �մϴ�.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    // ���� ������Ʈ
    products[id].stock_income += quantity;
    products[id].stock_current += quantity;
    products[id].price = price;
    printf("ID %d (%s)�� %d�� �԰� �Ϸ�. ���� ���: %d\n", id, products[id].name, quantity, products[id].stock_current);
}

// (2) �Ǹ� ó�� �Լ�
void handle_sale(Product products[], int count) 
{
    int id, quantity;
    printf("\n<< 2. �Ǹ� >>\n��ǰ ID (1~%d): ", count);
    if (scanf("%d", &id) != 1 || id < 1 || id > count) 
    {
        printf("�߸��� ��ǰ ��ȣ�Դϴ�.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    if (strcmp(products[id].name, "(���Է�)") == 0) 
    {
        printf("��ǰ�� ��ϵ��� �ʾҽ��ϴ�.\n"); return;
    }

    printf("��ǰ��: %s, ���� ���: %d\n�Ǹ� ����: ", products[id].name, products[id].stock_current);
    if (scanf("%d", &quantity) != 1 || quantity <= 0) 
    {
        printf("������ 1�� �̻��̾�� �մϴ�.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    // ��� �� ���� Ȯ��
    if (quantity > products[id].stock_current)
    {
        printf("��� ����! ���� ���: %d��\n", products[id].stock_current); return;
    }
    if (products[id].price == 0)
    {
        printf("�Ǹ� ������ 0���Դϴ�.\n"); return;
    }

    // ���� ������Ʈ
    products[id].stock_sold += quantity;
    products[id].stock_current -= quantity;
    products[id].total_revenue += (long long)quantity * products[id].price;

    printf("ID %d (%s) %d�� �Ǹ� �Ϸ�. �Ǹ� �ݾ�: %lld��\n", id, products[id].name, quantity, (long long)quantity * products[id].price);
    if (products[id].stock_current == 0) printf("��� ���� �˸�.\n");
}

// (3) ���� ��ǰ ���� ��ȸ/���� �Լ�
void handle_individual_info(Product products[], int count) 
{
    int id, sub_menu;
    printf("\n<< 3. ������ǰ���� >>\n1. ��ǰ�� ����\n2. ��Ȳ ��ȸ\n����: ");
    if (scanf("%d", &sub_menu) != 1) 
    { 
        printf("���� ����.\n"); clear_input_buffer(); return; 
    }
    printf("��ǰ ID (1~%d): ", count);
    if (scanf("%d", &id) != 1 || id < 1 || id > count)
    {
        printf("�߸��� ID.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    if (sub_menu == 1) 
    { // ��ǰ�� ����
        printf("�� ��ǰ�� �Է� (����: %s): ", products[id].name);
        if (fgets(products[id].name, MAX_NAME_LEN, stdin) != NULL)
            products[id].name[strcspn(products[id].name, "\n")] = 0;
        printf("��ǰ���� '%s'�� �����Ǿ����ϴ�.\n", products[id].name);
    }
    else if (sub_menu == 2) 
    { // ��Ȳ ��ȸ
        if (strcmp(products[id].name, "(���Է�)") == 0) 
        { 
            printf("��ǰ�� �̵���Դϴ�.\n"); return; 
        }
        printf("\n--- ID %d (%s) ��Ȳ ---\n", id, products[id].name);
        printf("�Ǹ� ����\t: %d��\n�԰� ����\t: %d��\n�Ǹ� ����\t: %d��\n���� ���\t: %d��\n�� �Ǹ� �ݾ�\t: %lld��\n",
            products[id].price, products[id].stock_income, products[id].stock_sold,
            products[id].stock_current, products[id].total_revenue);
    }
    else 
    {
        printf(" �߸��� �����Դϴ�.\n");
    }
}

// (4) ��ü ��Ȳ ��ȸ �Լ�
void handle_overall_status(Product products[], int count)
{
    printf("\n<< 4. ��ü ��ǰ ��Ȳ >>\n");
    printf("ID | ��ǰ�� | ��� | �԰� | �Ǹ� | ���� | �Ѹ���\n");
    printf("----------------------------------------------------------\n");

    long long overall_revenue = 0;
    int total_sold = 0, total_income = 0;
    int max_id = 0, min_id = 0; // �ִ�/�ּ� �Ǹ� ��ǰ ID

    for (int i = 1; i <= count; i++) 
    {
        // �̵�� ��ǰ�� �ǳʶ�
        if (strcmp(products[i].name, "(���Է�)") == 0) continue;

        // ���̺� ���
        printf("%-3d| %-7s | %-4d | %-4d | %-4d | %-5d | %-10lld\n",
            i, products[i].name, products[i].stock_current, products[i].stock_income,
            products[i].stock_sold, products[i].price, products[i].total_revenue);

        // ��ü �հ� ���
        overall_revenue += products[i].total_revenue;
        total_sold += products[i].stock_sold;
        total_income += products[i].stock_income;

        // �ִ�/�ּ� �Ǹ� ��ǰ ã�� (ù ��° ��� ��ǰ�� �ʱⰪ���� ����)
        if (max_id == 0) 
        { 
            max_id = min_id = i; 
        }
        else 
        {
            if (products[i].stock_sold > products[max_id].stock_sold) max_id = i;
            if (products[i].stock_sold < products[min_id].stock_sold) min_id = i;
        }
    }

    printf("----------------------------------------------------------\n");
    printf("�� �԰�: %d, �� �Ǹ�: %d\n", total_income, total_sold);
    printf("�� �Ǹ���: %.2f%%\n", total_income > 0 ? (double)total_sold / total_income * 100 : 0.0);
    printf("�� �Ǹ� �ݾ�: %lld ��\n", overall_revenue);

    // �Ǹŷ� ���� �� ��� ���� �˸�
    if (max_id != 0) 
    {
        printf("�ִ� �Ǹ�: ID %d (%s), %d��\n", max_id, products[max_id].name, products[max_id].stock_sold);
        printf("�ּ� �Ǹ�: ID %d (%s), %d��\n", min_id, products[min_id].name, products[min_id].stock_sold);
    }
    for (int i = 1; i <= count; i++) 
    {
        if (products[i].stock_current <= 2 && strcmp(products[i].name, "(���Է�)") != 0)
            printf("��� ����: ID %d (%s), ���: %d��\n", i, products[i].name, products[i].stock_current);
    }
}

// (5) ��ǰ ���� �Լ� (���̳ʸ� ���Ͽ� ����)
void save_data(Product products[], int count) 
{
    FILE* fp = fopen(DATA_FILE, "wb"); 
    if (fp == NULL) 
    {
        perror("? ���� ���� ����"); return; 
    }

    // products[1] ��ġ���� count ������ Product ����ü ��ü�� ���Ͽ� ����
    size_t written = fwrite(&products[1], sizeof(Product), count, fp);

    if (written == (size_t)count)
    {
        printf("��ǰ ���� %d���� '%s' ���Ͽ� ���������� ����Ǿ����ϴ�.\n", count, DATA_FILE);
    }
    else 
    {
        printf("���� �� ���� �߻�.\n");
    }
    fclose(fp);
}

// (6) ��ǰ �ҷ����� �Լ� (���̳ʸ� ���Ͽ��� �б�)
void load_data(Product products[], int count) 
{
    FILE* fp = fopen(DATA_FILE, "rb"); 
    if (fp == NULL) 
    { 
        perror("���� �ҷ����� ���� (����� ������ ����)"); 
        return; 
    }

    // ���Ͽ��� count ������ Product ����ü �����͸� products[1] ��ġ���� �о��
    size_t read = fread(&products[1], sizeof(Product), count, fp);

    if (read == (size_t)count) 
    {
        printf("��ǰ ���� %d���� '%s' ���Ͽ��� ���������� �ҷ��Խ��ϴ�.\n", count, DATA_FILE);
    }
    else 
    {
        printf("���� ���� ����. �Ϻ� �����͸� �ҷ��Խ��ϴ�.\n");
    }
    fclose(fp);
}