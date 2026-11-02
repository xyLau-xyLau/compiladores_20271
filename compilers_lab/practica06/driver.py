class Node:
    """Clase para representar cada nodo del Árbol Sintáctico (AST)."""
    def __init__(self, value, children=None):
        self.value = value
        self.children = children if children is not None else []

    def format_tree(self, prefix="", is_last=True, is_root=True):
        """Genera la representación visual en texto"""
        lines = []
        if is_root:
            lines.append(self.value)
            new_prefix = ""
        else:
            connector = "└── " if is_last else "├── "
            lines.append(prefix + connector + self.value)
            new_prefix = prefix + ("    " if is_last else "│   ")

        count = len(self.children)
        for i, child in enumerate(self.children):
            is_child_last = (i == count - 1)
            lines.extend(child.format_tree(new_prefix, is_child_last, is_root=False))

        return "\n".join(lines) if is_root else lines


PRODUCTIONS = {
    1: ('S', ['L', '=', 'R']),
    2: ('S', ['R']),
    3: ('L', ['*', 'R']),
    4: ('L', ['id']),
    5: ('R', ['L'])
}

LALR_TABLE = {
    0: {
        '*':  ('shift', 4),
        'id': ('shift', 5),
        'S':  ('goto', 1),
        'L':  ('goto', 2),
        'R':  ('goto', 3)
    },
    1: {
        '$':  ('accept', None)
    },
    2: {
        '=':  ('shift', 6),
        '$':  ('reduce', 5)
    },
    3: {
        '$':  ('reduce', 2)
    },
    4: {
        '*':  ('shift', 4),
        'id': ('shift', 5),
        'R':  ('goto', 7),
        'L':  ('goto', 8)
    },
    5: {
        '=':  ('reduce', 4),
        '$':  ('reduce', 4)
    },
    6: {
        '*':  ('shift', 4),
        'id': ('shift', 5),
        'R':  ('goto', 9),
        'L':  ('goto', 8)
    },
    7: {
        '=':  ('reduce', 3),
        '$':  ('reduce', 3)
    },
    8: {
        '=':  ('reduce', 5),
        '$':  ('reduce', 5)
    },
    9: {
        '$':  ('reduce', 1)
    }
}


def parse_lalr1(tokens):
    """
    Ejecuta el ciclo shift/reduce consultando la matriz unificada LALR_TABLE.
    """
    input_tokens = list(tokens)
    if not input_tokens or input_tokens[-1] != '$':
        input_tokens.append('$')

    state_stack = [0]
    node_stack = []
    ip = 0  # Puntero a token de entrada

    while True:
        current_state = state_stack[-1]
        current_token = input_tokens[ip]

        # Consulta unificada en la matriz de parseo para el token de entrada
        if current_token not in LALR_TABLE.get(current_state, {}):
            return False, f"Error sintáctico: Token no esperado '{current_token}' en el estado {current_state}.", None

        action_type, target = LALR_TABLE[current_state][current_token]

        # --- ACCIÓN SHIFT ---
        if action_type == 'shift':
            state_stack.append(target)
            node_stack.append(Node(current_token))
            ip += 1

        # --- ACCIÓN REDUCE ---
        elif action_type == 'reduce':
            rule_num = target
            lhs, rhs = PRODUCTIONS[rule_num]
            pop_count = len(rhs)

            # Desapilar k elementos
            children = []
            for _ in range(pop_count):
                state_stack.pop()
                children.append(node_stack.pop())
            children.reverse()

            parent_node = Node(lhs, children)
            top_state = state_stack[-1]

            # Consulta del valor GOTO en la misma matriz unificada usando el No Terminal
            if lhs not in LALR_TABLE.get(top_state, {}):
                return False, f"Error en GOTO: Sin transición para no terminal '{lhs}' en el estado {top_state}.", None

            goto_action, next_state = LALR_TABLE[top_state][lhs]
            if goto_action != 'goto':
                return False, f"Error en GOTO: Entrada no válida para '{lhs}' en el estado {top_state}.", None

            state_stack.append(next_state)
            node_stack.append(parent_node)

        # --- ACCIÓN ACCEPT ---
        elif action_type == 'accept':
            ast_root = node_stack[0] if node_stack else None
            return True, "Cadena VÁLIDA (Aceptada)", ast_root


# -------------------------------------------------------------------
# Pruebas de Ejecución
# -------------------------------------------------------------------
def probar_cadena(tokens):
    print("=" * 50)
    print(f"Entrada: {tokens}")
    es_valida, mensaje, ast = parse_lalr1(tokens)
    print(f"Resultado: {mensaje}")
    if es_valida and ast:
        print("\nÁrbol Sintáctico (AST):")
        print(ast.format_tree())
    print("=" * 50 + "\n")


if __name__ == "__main__":
    "Cadenas válidas"
    probar_cadena(['id', '=', 'id'])
    probar_cadena(['*', '*', 'id'])
    probar_cadena(['*', 'id', '=', 'id'])
    probar_cadena(['id', '=', '*', 'id'])
    probar_cadena(['*', '*', 'id', '=', '*', 'id'])

    "Cadenas inválidas"
    probar_cadena(['*', '=', 'id'])
    probar_cadena(['id', '=', '='])
    probar_cadena(['id', 'id', 'id'])
    probar_cadena(['id', '=', 'id', 'id'])
    probar_cadena(['id', '=', 'id', '=', 'id'])