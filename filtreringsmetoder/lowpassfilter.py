import os
import csv

# =========================
# Konfigurerbare verdier
# =========================
config = {
    "alpha": 0.2,
    "input_filename": "testmåling_06_05_25.csv",  # Må være i ../måledata/
    "suffix": "_lowpass",            # Ny fil får dette lagt til før .csv
}

# Mappestier
folder = "../måledata"
input_path = os.path.join(folder, config["input_filename"])

# Generer output-filnavn basert på input
basename, ext = os.path.splitext(config["input_filename"])
output_filename = basename + config["suffix"] + ext
output_path = os.path.join(folder, output_filename)

# =========================
# Eksponentielt glidende gjennomsnitt
# =========================
def low_pass_filter(prev, new, alpha):
    return [alpha * n + (1 - alpha) * p for p, n in zip(prev, new)]

# =========================
# Filtreringsfunksjon
# =========================
def filtrer_csv_data():
    print(f"Leser rådata fra: {input_path}")

    with open(input_path, mode='r') as infile, open(output_path, mode='w', newline='') as outfile:
        reader = csv.DictReader(infile)
        felt_navn = reader.fieldnames
        writer = csv.DictWriter(outfile, fieldnames=felt_navn)
        writer.writeheader()

        for i, rad in enumerate(reader):
            if i == 0:
                # Første rad = init
                forrige = {k: float(v) if k != "timestamp" else v for k, v in rad.items()}
                writer.writerow(rad)
                continue

            ny_rad = {}
            for k in rad:
                if k == "timestamp":
                    ny_rad[k] = rad[k]
                else:
                    ny_val = float(rad[k])
                    prev_val = forrige[k]
                    filtrert = config["alpha"] * ny_val + (1 - config["alpha"]) * prev_val
                    ny_rad[k] = round(filtrert, 4)
                    forrige[k] = filtrert  # Oppdater for neste runde
            writer.writerow(ny_rad)

    print(f"Filtrert data lagret i: {output_path}")

if __name__ == "__main__":
    filtrer_csv_data()
