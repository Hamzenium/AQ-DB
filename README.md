flowchart TD

%% =========================
%% CLIENTS
%% =========================
C1[Client 1<br/>redis-cli]:::clientStyle
C2[Client 2<br/>microservice]:::clientStyle
C3[Client 3<br/>app]:::clientStyle
CN[Client N]:::clientStyle

%% =========================
%% SERVER LAYER
%% =========================
subgraph server ["🌐 SERVER LAYER"]
    TCP[TCP Server<br/>Port 6379<br/>Accept Connections]:::serverStyle
end

%% =========================
%% EVENT LOOP
%% =========================
subgraph eventloop ["⚡ EVENT LOOP LAYER"]
    EL[Event Loop<br/>epoll/kqueue]:::eventStyle
    READ[Readable Events]:::eventStyle
    WRITE[Writable Events]:::eventStyle
end

%% =========================
%% CONNECTIONS
%% =========================
subgraph connections ["🔌 CONNECTION LAYER"]
    CONN1[Connection 1<br/>Read + Write Buffers]:::connStyle
    CONN2[Connection 2<br/>Read + Write Buffers]:::connStyle
    CONNN[Connection N<br/>Read + Write Buffers]:::connStyle
end

%% =========================
%% PROTOCOL
%% =========================
subgraph protocol ["📋 PROTOCOL LAYER"]
    PARSER[RESP Parser<br/>*2 $3 GET $5 mykey → Command]:::protocolStyle
end

%% =========================
%% COMMAND LAYER
%% =========================
subgraph command ["⚙️ COMMAND DISPATCHER"]
    DISPATCH[Command Dispatcher]:::commandStyle
    GET[GET Handler]:::commandStyle
    SET[SET Handler]:::commandStyle
    DEL[DEL Handler]:::commandStyle
    INCR[INCR Handler]:::commandStyle
    OTHER[Other Commands]:::commandStyle
end

%% =========================
%% STORAGE LAYER
%% =========================
subgraph storage ["💾 STORAGE LAYER"]
    KV[KVStore<br/>hash(key) % N]:::storageStyle
end

%% =========================
%% SHARDS
%% =========================
subgraph shards ["🗄️ SHARDED DATA"]
    S0[Shard 0<br/>HashMap]:::shardStyle
    S1[Shard 1<br/>HashMap]:::shardStyle
    S2[Shard 2<br/>HashMap]:::shardStyle
    SN[Shard N<br/>HashMap]:::shardStyle
end


%% =========================
%% FLOWS
%% =========================

%% Clients → Server
C1 -->|TCP Connection| TCP
C2 -->|TCP Connection| TCP
C3 -->|TCP Connection| TCP
CN -->|TCP Connection| TCP

%% Server → Event Loop
TCP -->|Register Socket| EL

%% Event Loop events
EL --> READ
EL --> WRITE

%% READ → Connections
READ --> CONN1
READ --> CONN2
READ --> CONNN

%% Connections → Parser
CONN1 -->|Bytes| PARSER
CONN2 -->|Bytes| PARSER
CONNN -->|Bytes| PARSER

%% Parser → Dispatcher
PARSER -->|Parsed Command| DISPATCH

%% Dispatcher → Command Handlers
DISPATCH --> GET
DISPATCH --> SET
DISPATCH --> DEL
DISPATCH --> INCR
DISPATCH --> OTHER

%% Command → Storage
GET --> KV
SET --> KV
DEL --> KV
INCR --> KV
OTHER --> KV

%% Storage → Shards
KV -->|hash(key)| S0
KV -->|hash(key)| S1
KV -->|hash(key)| S2
KV -->|hash(key)| SN

%% Shards → KVStore
S0 -.-> KV
S1 -.-> KV
S2 -.-> KV
SN -.-> KV

%% Back to dispatcher
KV -.-> DISPATCH

%% Dispatcher → Connections (RESP encode)
DISPATCH -.->|RESP Response| CONN1
DISPATCH -.-> CONN2
DISPATCH -.-> CONNN

%% Connections → Event Loop (write buffer ready)
CONN1 -.-> WRITE
CONN2 -.-> WRITE
CONNN -.-> WRITE

%% WRITE → Clients
WRITE -.->|Send Bytes| C1
WRITE -.-> C2
WRITE -.-> C3
WRITE -.-> CN


%% =========================
%% STYLES
%% =========================
classDef clientStyle fill:#E3F2FD,stroke:#1976D2,stroke-width:2px,color:#000
classDef serverStyle fill:#F3E5F5,stroke:#7B1FA2,stroke-width:2px,color:#000
classDef eventStyle fill:#FFF3E0,stroke:#F57C00,stroke-width:2px,color:#000
classDef connStyle fill:#E8F5E9,stroke:#388E3C,stroke-width:2px,color:#000
classDef protocolStyle fill:#FCE4EC,stroke:#C2185B,stroke-width:2px,color:#000
classDef commandStyle fill:#E0F2F1,stroke:#00796B,stroke-width:2px,color:#000
classDef storageStyle fill:#FFF9C4,stroke:#F9A825,stroke-width:2px,color:#000
classDef shardStyle fill:#FFEBEE,stroke:#D32F2F,stroke-width:2px,color:#000
