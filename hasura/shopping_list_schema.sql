CREATE TABLE public.assignees (
    id integer NOT NULL,
    group_id integer NOT NULL,
    name character varying NOT NULL
);

CREATE SEQUENCE public.assignees_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.assignees_id_seq OWNED BY public.assignees.id;

CREATE TABLE public.groups (
    id integer NOT NULL,
    name character varying NOT NULL
);

CREATE SEQUENCE public.groups_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.groups_id_seq OWNED BY public.groups.id;

CREATE TABLE public.lists (
    id integer NOT NULL,
    group_id integer NOT NULL,
    date date NOT NULL
);

CREATE SEQUENCE public.lists_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.lists_id_seq OWNED BY public.lists.id;

CREATE TABLE public.products (
    id integer NOT NULL,
    group_id integer NOT NULL,
    name character varying NOT NULL
);

CREATE SEQUENCE public.products_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.products_id_seq OWNED BY public.products.id;

CREATE TABLE public.products_lists (
    list_id integer NOT NULL,
    product_id integer NOT NULL,
    note character varying NOT NULL
);

ALTER TABLE ONLY public.assignees ALTER COLUMN id SET DEFAULT nextval('public.assignees_id_seq'::regclass);

ALTER TABLE ONLY public.groups ALTER COLUMN id SET DEFAULT nextval('public.groups_id_seq'::regclass);

ALTER TABLE ONLY public.lists ALTER COLUMN id SET DEFAULT nextval('public.lists_id_seq'::regclass);

ALTER TABLE ONLY public.products ALTER COLUMN id SET DEFAULT nextval('public.products_id_seq'::regclass);

ALTER TABLE ONLY public.assignees
    ADD CONSTRAINT assignees_group_id_name_key UNIQUE (group_id, name);

ALTER TABLE ONLY public.assignees
    ADD CONSTRAINT assignees_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.groups
    ADD CONSTRAINT groups_name_key UNIQUE (name);

ALTER TABLE ONLY public.groups
    ADD CONSTRAINT groups_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.lists
    ADD CONSTRAINT lists_group_id_date_key UNIQUE (group_id, date);

ALTER TABLE ONLY public.lists
    ADD CONSTRAINT lists_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.products
    ADD CONSTRAINT products_group_id_name_key UNIQUE (group_id, name);

ALTER TABLE ONLY public.products_lists
    ADD CONSTRAINT products_lists_pkey PRIMARY KEY (list_id, product_id);

ALTER TABLE ONLY public.products
    ADD CONSTRAINT products_pkey PRIMARY KEY (id);


ALTER TABLE ONLY public.assignees
    ADD CONSTRAINT assignees_group_id_fkey FOREIGN KEY (group_id) REFERENCES public.groups(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY public.lists
    ADD CONSTRAINT lists_group_id_fkey FOREIGN KEY (group_id) REFERENCES public.groups(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY public.products
    ADD CONSTRAINT products_group_id_fkey FOREIGN KEY (group_id) REFERENCES public.groups(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY public.products_lists
    ADD CONSTRAINT products_lists_list_id_fkey FOREIGN KEY (list_id) REFERENCES public.lists(id) ON UPDATE RESTRICT ON DELETE RESTRICT;

ALTER TABLE ONLY public.products_lists
    ADD CONSTRAINT products_lists_product_id_fkey FOREIGN KEY (product_id) REFERENCES public.products(id) ON UPDATE RESTRICT ON DELETE RESTRICT;
