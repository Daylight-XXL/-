#include <stdio.h>
#include <stdlib.h>
typedef struct s_1 {
	int c;
	struct s_1 * l_child;
	struct s_1 * r_child;
}node;
void build_tree(int *s, int x, int y,node * p_node) {
	int c_1 = -1, c_2 = -1, p = 0,i;
	if ((y - x) == 1) {
		p_node->c = s[x];
		return;
	}
	for (i = x; i < y; i++) {
		switch (s[i]){
		case -1:
			p++;
			break;
		case -2:
			p--;
			break;
		case -3:
		case -4:
			if (!p) {
				c_1 = i;
			}
			break;
		case -5:
		case -6:
			if (!p) {
				c_2 = i;
			}
			break;
		default:
			break;
		}
	}
	if (c_1 < 0) {
		c_1 = c_2; 
	}
	if (c_1 < 0) {
		build_tree(s, x + 1, y - 1, p_node);
		return;
	}
	else{
		p_node->c = s[c_1];
		node * ptr_l = (node *)malloc(sizeof(node));
		ptr_l->l_child = NULL;
		ptr_l->r_child = NULL;
		p_node->l_child = ptr_l;
		build_tree(s, x , c_1, p_node->l_child);
		node * ptr_r = (node *)malloc(sizeof(node));
		ptr_r->l_child = NULL;
		ptr_r->r_child = NULL;
		p_node->r_child = ptr_r;
		build_tree(s, c_1 + 1, y, p_node->r_child);
		return;
	}
}
int cala(node * p_node) {
	switch (p_node->c) {
	case -3:
		return cala(p_node->l_child) - cala(p_node->r_child);
	case -4:
		return cala(p_node->l_child) + cala(p_node->r_child);
	case -5:
		return cala(p_node->l_child) * cala(p_node->r_child);
	case -6:
		return cala(p_node->l_child) / cala(p_node->r_child);
	default:
		return p_node->c;
	}
}
int main() {
	node root;
	root.l_child = NULL;
	root.r_child = NULL;
	int i = 0;
	int str[1024] = {0};
	int if_number = 0;
	char c;
	while (1) {
		scanf("%c", &c);
		if (c == '\n') {
			break;
		}
		if (c >= '0' && c <= '9') {
			str[i] = str[i] * 10 + c - '0';
			if_number = 1;
		}
		else {
			if (if_number) {
				if_number = 0;
				i++;
			}
			switch (c){
			case'(':
				str[i] = -1;
				break;
			case')':
				str[i] = -2;
				break;
			case'-':
				str[i] = -3;
				break;
			case'+':
				str[i] = -4;
				break;
			case'*':
				str[i] = -5;
				break;
			case'/':
				str[i] = -6;
				break;
			default:
				break;
			}
			i++;
		}
	}
	build_tree(str, 0, i+1, &root);
	printf("%d", cala(&root));
}
