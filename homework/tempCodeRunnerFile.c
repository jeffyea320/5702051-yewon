
void InsertMaxHeapTree(HeapType *h, element item)
{
    int i;
    i = ++(h->heap_size); // 힙 크기를 하나 증가

    /* 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정 */
    // i가 루트노드(index:1)이 아니고, 삽입할 item의 값이 i의 부모노(index:i/2) 보다 크면
    while ((i != 1) && (item.key > h->heap[i / 2].key))
    {
        // i번째 노드와 부모 노드를 교환한다.
        h->heap[i] = h->heap[i / 2];
        // 한 레벨 위로 올라간다.
        i /= 2;
    }
    h->heap[i] = item; // 새로운 노드를 삽입
}

print_codes(e.ptree, codes, top);
    destroy_tree(e.ptree);
    free(heap);

