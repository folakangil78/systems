int * size(LinkedList * list) {
	Node * temp = list -> head;
	
	int size = 0;
	
	if temp == NULL) {
		return 0;
	}

	else {
		while (temp != list -> tail) {
			size++;
			temp = temp -> next;
		}
		size++;
	}
	
	return size;

}

Node * middle_val(LinkedList * list) {
	int size = size(list);
	
	int index = size / 2
	Node * temp = list -> head;

	while (index != 0) {
		temp = temp -> next;
		index--;
	}

	return temp; // would need to reference value behind struct if function returning an int instead of node
}

void delete_last(LinkedList * list) {
	Node * temp = list -> head;
	while (temp -> next != list -> tail) {
		temp = temp -> next;
	}
	free(temp -> next) // assuming dynam allocated
	temp -> next = NULL;
	list -> tail = temp;
}
