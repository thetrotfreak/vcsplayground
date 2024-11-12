import uuid
from fastapi import FastAPI
from pydantic import BaseModel


class Foo(BaseModel):
    username: str
    password: str


app = FastAPI()


@app.get("/")
async def root():
    return {"detail": "Hello, World!"}


@app.post("/post", status_code=201)
async def foo_post(foo: Foo):
    return {"detail": uuid.uuid4().urn}
