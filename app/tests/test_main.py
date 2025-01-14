import pytest

from fastapi.testclient import TestClient

from main import app


class TestMain:
  @pytest.mark.asyncio
  async def test_foo(self):
    with TestClient(app) as client:
      response = client.get("/")
      assert response.status_code == 200
      assert "message" in response.json()
