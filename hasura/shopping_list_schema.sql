CREATE TABLE assignees (
    id integer NOT NULL,
    group_id integer NOT NULL,
    name character varying NOT NULL
);

CREATE SEQUENCE assignees_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE assignees_id_seq OWNED BY assignees.id;

CREATE TABLE groups (
    id integer NOT NULL,
    name character varying NOT NULL
);

CREATE SEQUENCE groups_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE groups_id_seq OWNED BY groups.id;

CREATE TABLE lists (
    id integer NOT NULL,
    group_id integer NOT NULL,
    date date NOT NULL
);

CREATE SEQUENCE lists_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE lists_id_seq OWNED BY lists.id;

CREATE TABLE products (
    id integer NOT NULL,
    group_id integer NOT NULL,
    name character varying NOT NULL
);

CREATE SEQUENCE products_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE products_id_seq OWNED BY products.id;

CREATE TABLE products_lists (
    list_id integer NOT NULL,
    product_id integer NOT NULL,
    note character varying NOT NULL
);

ALTER TABLE ONLY assignees ALTER COLUMN id SET DEFAULT nextval('assignees_id_seq'::regclass);

ALTER TABLE ONLY groups ALTER COLUMN id SET DEFAULT nextval('groups_id_seq'::regclass);

ALTER TABLE ONLY lists ALTER COLUMN id SET DEFAULT nextval('lists_id_seq'::regclass);

ALTER TABLE ONLY products ALTER COLUMN id SET DEFAULT nextval('products_id_seq'::regclass);

ALTER TABLE ONLY assignees
    ADD CONSTRAINT assignees_group_id_name_key UNIQUE (group_id, name);

ALTER TABLE ONLY assignees
    ADD CONSTRAINT assignees_pkey PRIMARY KEY (id);

ALTER TABLE ONLY groups
    ADD CONSTRAINT groups_name_key UNIQUE (name);

ALTER TABLE ONLY groups
    ADD CONSTRAINT groups_pkey PRIMARY KEY (id);

ALTER TABLE ONLY lists
    ADD CONSTRAINT lists_group_id_date_key UNIQUE (group_id, date);

ALTER TABLE ONLY lists
    ADD CONSTRAINT lists_pkey PRIMARY KEY (id);

ALTER TABLE ONLY products
    ADD CONSTRAINT products_group_id_name_key UNIQUE (group_id, name);

ALTER TABLE ONLY products_lists
    ADD CONSTRAINT products_lists_pkey PRIMARY KEY (list_id, product_id);

ALTER TABLE ONLY products
    ADD CONSTRAINT products_pkey PRIMARY KEY (id);

ALTER TABLE ONLY assignees
    ADD CONSTRAINT assignees_group_id_fkey FOREIGN KEY (group_id) REFERENCES groups(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY lists
    ADD CONSTRAINT lists_group_id_fkey FOREIGN KEY (group_id) REFERENCES groups(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY products
    ADD CONSTRAINT products_group_id_fkey FOREIGN KEY (group_id) REFERENCES groups(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY products_lists
    ADD CONSTRAINT products_lists_list_id_fkey FOREIGN KEY (list_id) REFERENCES lists(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY products_lists
    ADD CONSTRAINT products_lists_product_id_fkey FOREIGN KEY (product_id) REFERENCES products(id) ON UPDATE RESTRICT ON DELETE RESTRICT;
